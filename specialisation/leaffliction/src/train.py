from PIL import Image
import os
import numpy as np
from sklearn.model_selection import train_test_split
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense, Dropout
import shutil
import cv2
from utils.process_augment import copy_and_process_images
from tqdm import tqdm
from sklearn.model_selection import train_test_split

from plantcv import plantcv as pcv

def split_data_into_train_test(source_dir, train_dir, test_dir, train_ratio=0.8):
    """
    Splits images from source directory into training and testing directories.
    Each category in the source directory is treated separately.

    :param source_dir: Directory containing categorized images.
    :param train_dir: Directory to store training images.
    :param test_dir: Directory to store testing images.
    :param train_ratio: Ratio of training data (default is 0.8).
    """
    # Create the train and test directories if they don't exist
    os.makedirs(train_dir, exist_ok=True)
    os.makedirs(test_dir, exist_ok=True)

    # List all category directories in the source directory
    categories = os.listdir(source_dir)
    print(categories)

    # Iterate over each category
    for category in categories:
        category_path = os.path.join(source_dir, category)

        # Check if it's a directory
        if os.path.isdir(category_path):
            # Create category directories in train and test directories
            os.makedirs(os.path.join(train_dir, category), exist_ok=True)
            os.makedirs(os.path.join(test_dir, category), exist_ok=True)

            # Get all images in the category directory
            images = os.listdir(category_path)

            # Split the images into train and test sets
            train_images, test_images = train_test_split(images, train_size=train_ratio, random_state=42)

            # Copy each image into the respective train and test directories
            for image in train_images:
                source = os.path.join(category_path, image)
                destination = os.path.join(train_dir, category, image)
                shutil.copy(source, destination)
                
            for image in test_images:
                source = os.path.join(category_path, image)
                destination = os.path.join(test_dir, category, image)
                shutil.copy(source, destination)
        

def resize_images(directory):
    for root, dirs, files in tqdm(os.walk(directory)):
        for file in files:
            if file.lower().endswith(('.png', '.jpg', '.jpeg')):  # Checking for image file types
                image_path = os.path.join(root, file)
                image = Image.open(image_path)
                image = image.resize((250, 250))
                image.save(image_path)

def build_model():
    model = Sequential([
        Conv2D(16, (3, 3), activation='relu', input_shape=(250, 250, 3)),
        MaxPooling2D(2, 2),
        Conv2D(32, (3, 3), activation='relu'),
        MaxPooling2D(2, 2),
        Conv2D(64, (3, 3), activation='relu'),
        MaxPooling2D(2, 2),
        Flatten(),
        Dense(512, activation='relu'),
        Dropout(0.3),
        Dense(8, activation='softmax')  # Number of classes
    ])
    return model

image_number = 0

def extract_leaf(original_image):
    global image_number
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
    
    #save the leaf shape incrementing the image number
    cv2.imwrite(f'images_transformed/leaf_shape_{image_number}.png', leaf_shape)
    image_number += 1

    
    return leaf_shape

if __name__ == "__main__":
    
    # split_data_into_train_test('images', 'train', 'test')
    
    #clean the directories
    shutil.rmtree('images_transformed')
    #create the directories
    os.makedirs('images_transformed', exist_ok=True)

    model = build_model()
    
    # Compile the model
    model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    model.summary()
    
    # Create an ImageDataGenerator and do Image Augmentation
    train_datagen = ImageDataGenerator(rescale=1.0 / 255.0, # standardizing the pixel values
                                       rotation_range=40, # random rotation 
                                       width_shift_range=0.1, # shifting the images
                                       height_shift_range=0.1, # shifting the images
                                       shear_range=0.1, # shearing the images
                                       zoom_range=0.1, # zooming the images
                                       horizontal_flip=True, #randomly flipping the images
                                       fill_mode='nearest', # filling the missing pixels with the nearest pixel
                                       preprocessing_function=extract_leaf
                                       )
    validation_datagen = ImageDataGenerator(rescale=1.0 / 255.0,
                                            preprocessing_function=extract_leaf
                                            )# standardizing the pixel values
    
    # Flow training images in batches of 20 using train_datagen generator
    train_generator = train_datagen.flow_from_directory('train',
                                                        batch_size=20,
                                                        class_mode='sparse', # sparse categorical crossentropy
                                                        target_size=(250, 250)) # resizing the images to 250x250
    print("Train generator label value counts:", train_generator.labels)
    
    # Flow validation images in batches of 20 using test_datagen generator
    validation_generator = validation_datagen.flow_from_directory('test',
                                                                  batch_size=20,
                                                                  class_mode='sparse',
                                                                  target_size=(250, 250),
                                                                  shuffle=True
                                                                  )
    # Train the model
    history = model.fit(train_generator,
                        validation_data=validation_generator,
                        epochs=10,
                        verbose=1)
    
    #evaluate the model
    model.evaluate(validation_generator)
    
    #save the model
    model.save('model.h5')
    