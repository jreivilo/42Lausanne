from PIL import Image, ImageOps, ImageTransform, ImageFilter
import os
import argparse
from tqdm import tqdm
import shutil

def copy_and_process_images(original_folder_path, new_folder_path):
    total_images = 0
    for root, dirs, files in os.walk(original_folder_path):
        for filename in files:
            if filename.lower().endswith(".jpg"):
                total_images += 1

    with tqdm(total=total_images, desc="Processing images") as pbar:
        for root, dirs, files in os.walk(original_folder_path):
            for filename in files:
                if filename.lower().endswith(".jpg"):
                    # Construct the original file path
                    original_file_path = os.path.join(root, filename)

                    # Create a new path under the new folder, maintaining the subdirectory structure
                    relative_path = os.path.relpath(root, original_folder_path)
                    new_root = os.path.join(new_folder_path, relative_path)
                    if not os.path.exists(new_root):
                        os.makedirs(new_root)
                    new_file_path = os.path.join(new_root, filename)

                    # Copy the image to the new location
                    shutil.copy2(original_file_path, new_file_path)

                    # Apply transformations to the image in its new location
                    apply_augmentations(new_file_path)

                    # Update progress
                    pbar.update(1)

def apply_radial_distortion(image, strength=1):
	# Radial distortion effect
	width, height = image.size
	x_center, y_center = width / 2, height / 2
	new_image = Image.new("RGB", (width, height))

	for x in range(width):
		for y in range(height):
			# Shift x and y coordinates by a factor based on distance from the center
			factor = 1 + strength * ((x - x_center) ** 2 + (y - y_center) ** 2) / (2 * x_center ** 2)
			new_x, new_y = int(x_center + (x - x_center) * factor), int(y_center + (y - y_center) * factor)
			if 0 <= new_x < width and 0 <= new_y < height:
				new_image.putpixel((x, y), image.getpixel((new_x, new_y)))

	return new_image

def apply_augmentations(file_path):
	# Load the image
	original_image = Image.open(file_path)
	base, extension = os.path.splitext(file_path)
	base = base.replace('./', '')  # Adjusting base for saving files

	# Flip the image horizontally
	flipped_image = ImageOps.mirror(original_image)
	flipped_image.save(f'{base}_flip{extension}')

	# Rotate the image by 90 degrees
	rotated_image = original_image.rotate(90, expand=True)
	rotated_image.save(f'{base}_rotate{extension}')

	# blur the image
	blurred_image = original_image.filter(ImageFilter.BLUR)
	blurred_image.save(f'{base}_blur{extension}')

	# contrast the image
	contrasted_image = ImageOps.autocontrast(original_image)
	contrasted_image.save(f'{base}_contrast{extension}')

	# Crop the image (cropping the central part)
	width, height = original_image.size
	left = width / 4
	top = height / 4
	right = 3 * width / 4
	bottom = 3 * height / 4
	cropped_image = original_image.crop((left, top, right, bottom))
	cropped_image.save(f'{base}_crop{extension}')

	# illuminate the image
	illuminated_image = ImageOps.solarize(original_image)
	illuminated_image.save(f'{base}_illuminate{extension}')
	
 
if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="Apply various augmentations to an image.")
	parser.add_argument("file_path", type=str, help="Path to the image file to be augmented")
	args = parser.parse_args()

	apply_augmentations(args.file_path)
