import os
import sys
import shutil
import numpy as np
import cv2
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from sklearn.metrics import accuracy_score


# Define class names
class_names = [
    "Apple_black_rot", "Apple_healthy", "Apple_rust", "Apple_scab",
    "Grape_black_rot", "Grape_esca", "Grape_healthy", "Grape_spot"
]


def extract_leaf(original_image: np.ndarray) -> np.ndarray:
    """
    Extract leaf shape from an image using LAB color space and thresholding.

    :param original_image: Original RGB image
    :return: Masked image of the leaf shape
    """
    lab_image = cv2.cvtColor(src=original_image, code=cv2.COLOR_RGB2LAB)
    l_channel, a_channel, b_channel = cv2.split(m=lab_image)

    # Convert a_channel to 8-bit
    a_channel_8bit = cv2.convertScaleAbs(src=a_channel)

    # Thresholding on the a-channel (which should highlight the green parts)
    _, binary_image = cv2.threshold(
        src=a_channel_8bit, thresh=120, maxval=255,
        type=cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU
    )

    # Morphological operations to clean up the mask
    kernel = np.ones((5, 5), np.uint8)
    binary_image = cv2.morphologyEx(
        src=binary_image, op=cv2.MORPH_CLOSE, kernel=kernel
    )
    binary_image = cv2.morphologyEx(
        src=binary_image, op=cv2.MORPH_OPEN, kernel=kernel
    )

    # Find contours
    contours, _ = cv2.findContours(
        image=binary_image, mode=cv2.RETR_EXTERNAL,
        method=cv2.CHAIN_APPROX_SIMPLE
    )

    # Filter contours based on area or other criteria
    leaf_contours = [cnt for cnt in contours if cv2.contourArea(cnt) > 1000]

    # Create a mask from the contours
    mask = np.zeros_like(binary_image)
    cv2.drawContours(
        image=mask, contours=leaf_contours, contourIdx=-1, color=(255),
        thickness=cv2.FILLED
    )

    # Apply the mask to the original image
    leaf_shape = cv2.bitwise_and(
        src1=original_image, src2=original_image, mask=mask
    )

    return leaf_shape


def load_test_data(test_dir: str, batch_size: int = 1) -> ImageDataGenerator:
    """
    Prepares the test data for evaluation.

    :param test_dir: Directory containing the test data.
    :param batch_size: Number of images per batch (default 1).
    :return: Returns a generator for the test data.
    """
    test_datagen = ImageDataGenerator(
        rescale=1.0/255, preprocessing_function=extract_leaf
    )
    print(test_dir)
    test_generator = test_datagen.flow_from_directory(
        directory=test_dir, class_mode='categorical', target_size=(250, 250),
        shuffle=False
    )

    # Checks whether the generator contains images
    if test_generator.samples == 0:
        print("Error: No images found in the specified path. Please check "
              "the path and ensure it contains valid images or repository.")
        sys.exit(1)

    return test_generator


def predict_single_image_with_generator(model, image_path: str):
    """
    Predicts the class of a single image using a generator.

    :param model: The trained model.
    :param image_path: Path to the image to predict.
    :return: Predicted class and expected class index.
    """
    # Obtain the expected class using the parent folder if possible
    expected_class_name = os.path.basename(os.path.dirname(image_path))
    expected_class_index = (
        class_names.index(expected_class_name) if expected_class_name in
        class_names else None
    )

    # Create a temporary directory for the single image
    temp_dir = "temp_single_image_dir"
    temp_subdir = os.path.join(temp_dir, "class_0")
    os.makedirs(temp_subdir, exist_ok=True)

    # Copy the image to the temporary directory
    shutil.copy(
        src=image_path,
        dst=os.path.join(temp_subdir, os.path.basename(image_path))
    )

    # Use ImageDataGenerator to load the single image
    test_datagen = ImageDataGenerator(
        rescale=1.0/255, preprocessing_function=extract_leaf
    )
    test_generator = test_datagen.flow_from_directory(
        directory=temp_dir, class_mode=None, target_size=(250, 250),
        batch_size=1, shuffle=False
    )

    # Predictions
    prediction = model.predict(x=test_generator)
    predicted_class = np.argmax(prediction, axis=1)[0]

    # Get the class label
    class_label = class_names[predicted_class]
    expected_class_label = (
        class_names[expected_class_index] if expected_class_index is not None
        else "Unknown"
    )

    # Display the predicted and expected class
    print(f"Prediction for {image_path}:")
    print(f"Predicted Class {predicted_class} ({class_label})")
    print(f"Expected Class {expected_class_index} ({expected_class_label})")

    # Clean up the temporary directory
    shutil.rmtree(path=temp_dir)
    return predicted_class, expected_class_index


def predict_and_evaluate(model, test_generator) -> float:
    """
    Makes predictions with the model and evaluates its accuracy.

    :param model: The trained model.
    :param test_generator: Generator for the test data.
    :return: The accuracy of the model on the test data.
    """
    # Predictions
    predictions = model.predict(x=test_generator)
    predicted_classes = np.argmax(predictions, axis=1)

    # True labels
    true_classes = test_generator.classes

    print(f"True classes: {true_classes}")
    print(f"Predicted classes: {predicted_classes}")

    # Accuracy
    accuracy = accuracy_score(y_true=true_classes, y_pred=predicted_classes)
    return accuracy


if __name__ == "__main__":
    model_path = 'model.h5'
    model = load_model(filepath=model_path)

    if len(sys.argv) > 1:
        input_path = sys.argv[1]
        if os.path.isfile(input_path) and input_path.lower().endswith(
            ('.jpg', '.jpeg', '.png')
        ):
            # If only one image is supplied
            print(f"Single image provided: {input_path}")
            predict_single_image_with_generator(
                model=model,
                image_path=input_path
            )
        elif os.path.isdir(input_path):
            # If a directory is supplied
            print(f"Directory provided: {input_path}")
            test_generator = load_test_data(test_dir=input_path)
            accuracy = predict_and_evaluate(
                model=model, test_generator=test_generator
            )
            print(f"Accuracy on directory images: {accuracy * 100:.2f}%")
        else:
            print("Provided path is neither an image nor a directory.")
    else:
        # Default behavior if no arguments are passed
        test_dir = 'Unit_test_all'
        print("No argument passed, running evaluation on default test data.")
        test_generator = load_test_data(test_dir=test_dir)
        accuracy = predict_and_evaluate(
            model=model, test_generator=test_generator
        )
        print(f"Accuracy on Test Data: {accuracy * 100:.2f}%")
