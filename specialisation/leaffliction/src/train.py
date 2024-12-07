from PIL import Image
import os
import numpy as np
from sklearn.model_selection import train_test_split
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense
import shutil
import cv2
from augmentation import copy_and_process_images
from tqdm import tqdm
from tensorflow.keras.optimizers import Adam


def split_data_into_train_test(
    source_dir: str, train_dir: str, test_dir: str, train_ratio: float = 0.8
) -> None:
    """
    Splits images from source directory into training and testing directories.
    Each category in the source directory is treated separately.

    :param source_dir: Directory containing categorized images.
    :param train_dir: Directory to store training images.
    :param test_dir: Directory to store testing images.
    :param train_ratio: Ratio of training data (default is 0.8).
    """
    os.makedirs(train_dir, exist_ok=True)
    os.makedirs(test_dir, exist_ok=True)

    categories = os.listdir(source_dir)
    print(categories)

    for category in categories:
        category_path = os.path.join(source_dir, category)

        if os.path.isdir(category_path):
            os.makedirs(os.path.join(train_dir, category), exist_ok=True)
            os.makedirs(os.path.join(test_dir, category), exist_ok=True)

            images = os.listdir(category_path)
            train_images, test_images = train_test_split(
                images, train_size=train_ratio, random_state=42
            )

            for image in train_images:
                source = os.path.join(category_path, image)
                destination = os.path.join(train_dir, category, image)
                shutil.copy(source, destination)

            for image in test_images:
                source = os.path.join(category_path, image)
                destination = os.path.join(test_dir, category, image)
                shutil.copy(source, destination)


def resize_images(directory: str) -> None:
    for root, dirs, files in tqdm(os.walk(directory)):
        for file in files:
            if file.lower().endswith(('.png', '.jpg', '.jpeg')):
                image_path = os.path.join(root, file)
                image = Image.open(image_path)
                image = image.resize((250, 250))
                image.save(image_path)


def build_model() -> Sequential:
    model = Sequential([
        Conv2D(16, (3, 3), activation='relu', input_shape=(250, 250, 3)),
        MaxPooling2D(2, 2),
        Conv2D(32, (3, 3), activation='relu'),
        MaxPooling2D(2, 2),
        Conv2D(64, (3, 3), activation='relu'),
        MaxPooling2D(2, 2),
        Flatten(),
        Dense(256, activation='relu'),
        Dense(128, activation='relu'),
        Dense(8, activation='softmax')  # Number of classes
    ])
    return model


image_number = 0


def extract_leaf(original_image: np.ndarray) -> np.ndarray:
    global image_number
    lab_image = cv2.cvtColor(original_image, cv2.COLOR_RGB2LAB)
    l_channel, a_channel, b_channel = cv2.split(lab_image)

    a_channel_8bit = cv2.convertScaleAbs(a_channel)
    _, binary_image = cv2.threshold(
        a_channel_8bit, 120, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU
    )

    kernel = np.ones((5, 5), np.uint8)
    binary_image = cv2.morphologyEx(binary_image, cv2.MORPH_CLOSE, kernel)
    binary_image = cv2.morphologyEx(binary_image, cv2.MORPH_OPEN, kernel)

    contours, _ = cv2.findContours(
        binary_image, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
    )

    leaf_contours = [cnt for cnt in contours if cv2.contourArea(cnt) > 1000]
    mask = np.zeros_like(binary_image)
    cv2.drawContours(mask, leaf_contours, -1, (255), thickness=cv2.FILLED)

    leaf_shape = cv2.bitwise_and(original_image, original_image, mask=mask)
    file_path = f'images_transformed/leaf_shape_{image_number}.png'
    cv2.imwrite(file_path, leaf_shape)
    image_number += 1

    return leaf_shape


if __name__ == "__main__":
    copy_and_process_images('images', 'images_transformed')
    split_data_into_train_test('images', 'train', 'test')

    shutil.rmtree('images_transformed')
    os.makedirs('images_transformed', exist_ok=True)

    optimizer = Adam(learning_rate=0.001)
    model = build_model()
    model.compile(
        optimizer=optimizer,
        loss='categorical_crossentropy', metrics=['accuracy']
    )
    model.summary()

    train_datagen = ImageDataGenerator(
        rescale=1.0 / 255.0,
        rotation_range=40,
        width_shift_range=0.1,
        height_shift_range=0.1,
        shear_range=0.1,
        zoom_range=0.1,
        horizontal_flip=True,
        fill_mode='nearest',
        preprocessing_function=extract_leaf,
    )
    validation_datagen = ImageDataGenerator(
        rescale=1.0 / 255.0, preprocessing_function=extract_leaf
    )

    train_generator = train_datagen.flow_from_directory(
        'train', batch_size=20, class_mode='categorical',
        target_size=(250, 250), seed=42
    )
    print("Train generator label value counts:", train_generator.labels)

    validation_generator = validation_datagen.flow_from_directory(
        'Unit_test_all', class_mode='categorical', target_size=(250, 250),
        shuffle=True
    )

    history = model.fit(
        train_generator, validation_data=validation_generator, epochs=10,
        verbose=1
    )

    model.evaluate(validation_generator)
    model.save('model.h5')
