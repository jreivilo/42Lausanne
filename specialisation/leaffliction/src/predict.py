import numpy as np
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from sklearn.metrics import accuracy_score
import os
from plantcv import plantcv as pcv
import matplotlib.pyplot as plt
import math
import numpy as np
import cv2


def extract_leaf(original_image):
    # Convert to LAB color space
    lab_image = cv2.cvtColor(original_image, cv2.COLOR_RGB2LAB)
    l_channel, a_channel, b_channel = cv2.split(lab_image)

    # Convert a_channel to 8-bit
    a_channel_8bit = cv2.convertScaleAbs(a_channel)

    # Thresholding on the a-channel (which should highlight the green parts)
    _, binary_image = cv2.threshold(a_channel_8bit, 120, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)

    # Morphological operations to clean up the mask
    kernel = np.ones((5,5), np.uint8)
    binary_image = cv2.morphologyEx(binary_image, cv2.MORPH_CLOSE, kernel)
    binary_image = cv2.morphologyEx(binary_image, cv2.MORPH_OPEN, kernel)

    # Find contours
    contours, _ = cv2.findContours(binary_image, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Filter contours based on area or other criteria
    leaf_contours = [cnt for cnt in contours if cv2.contourArea(cnt) > 1000]

    # Create a mask from the contours
    mask = np.zeros_like(binary_image)
    cv2.drawContours(mask, leaf_contours, -1, (255), thickness=cv2.FILLED)

    # Apply the mask to the original image
    leaf_shape = cv2.bitwise_and(original_image, original_image, mask=mask)

    
    return leaf_shape

def load_test_data(test_dir, batch_size=1):
    """
    Prepares the test data for evaluation.
    
    :param test_dir: Directory containing the test data.
    :param batch_size: Number of images per batch (default 20).
    :return: Returns a generator for the test data.
    """
    test_datagen = ImageDataGenerator(rescale=1.0/255,
                                      preprocessing_function=extract_leaf)
    test_generator = test_datagen.flow_from_directory(test_dir,
                                                      batch_size=batch_size,
                                                      class_mode='sparse', 
                                                      target_size=(250, 250),
                                                      shuffle=False)
    return test_generator

def predict_and_evaluate(model, test_generator):
    """
    Makes predictions with the model and evaluates its accuracy.

    :param model: The trained model.
    :param test_generator: Generator for the test data.
    :return: The accuracy of the model on the test data.
    """
    # Predictions
    predictions = model.predict(test_generator)
    predicted_classes = np.argmax(predictions, axis=1)

    # True labels
    true_classes = test_generator.classes

    # Accuracy
    accuracy = accuracy_score(true_classes, predicted_classes)
    return accuracy

import sys
import cv2
import matplotlib.pyplot as plt

validation_datagen = ImageDataGenerator(rescale=1.0 / 255.0,
                                        preprocessing_function=extract_leaf
                                        )# standardizing the pixel values

if __name__ == "__main__":
    model_path = 'model.h5'
    test_dir = 'test'

    #if 1 argument is passed
    if len(sys.argv) == 2:
        image = cv2.imread(sys.argv[1])
        
        model = load_model(model_path)
        
        #sace the image 250x250
        image = cv2.resize(image, (250, 250))
        
        extracted_leaf = extract_leaf(image)
        
        # Predict the class
        prediction = model.predict(validation_datagen.flow(np.array([image])))
        
        # save images in folder predict_images with the name of the image
        cv2.imwrite(f"predict_images/extracted_lead.png", extracted_leaf)
        cv2.imwrite(f"predict_images/original_image.png", image)

        #transform the prediction to a string
        prediction = np.argmax(prediction)
        if prediction == 7:
            prediction = 'Apple_black_rot'
        elif prediction == 6:
            prediction = 'Apple_healthy'
        elif prediction == 5:
            prediction = 'Apple_rust'
        elif prediction == 4:
            prediction = 'Apple_scab'
        elif prediction == 3:
            prediction = 'Grape_Black_rot'
        elif prediction == 2:
            prediction = 'Grape_esca'
        elif prediction == 1:
            prediction = 'Grape_healthy'
        elif prediction == 0:
            prediction = 'Grape_spot'
            
        print(f"Prediction: {prediction}")
            

    else:
        # Load the model
        model = load_model(model_path)

        # Prepare the test data
        test_generator = load_test_data(test_dir)

        # Evaluate the model
        accuracy = predict_and_evaluate(model, test_generator)
        print(f"Accuracy on Test Data: {accuracy * 100:.2f}%")
