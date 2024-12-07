import os
import argparse
import shutil
from tqdm import tqdm
from PIL import Image, ImageOps, ImageFilter


def copy_and_process_images(
    original_folder_path: str,
    new_folder_path: str
) -> None:
    """
    Copy and apply transformations to images from the original folder to a
    new folder.

    :param original_folder_path: Path to the original folder containing images
    :param new_folder_path: Path to the new folder where images will be saved
    """
    total_images = sum(
        1 for _, _, files in os.walk(original_folder_path)
        if any(f.lower().endswith(".jpg") for f in files)
    )

    with tqdm(total=total_images, desc="Processing images") as pbar:
        for root, _, files in os.walk(original_folder_path):
            for filename in files:
                if filename.lower().endswith(".jpg"):
                    original_file_path = os.path.join(root, filename)
                    relative_path = os.path.relpath(root, original_folder_path)
                    new_root = os.path.join(new_folder_path, relative_path)
                    os.makedirs(new_root, exist_ok=True)
                    new_file_path = os.path.join(new_root, filename)

                    shutil.copy2(src=original_file_path, dst=new_file_path)
                    apply_augmentations(
                        file_path=new_file_path, save_to_augmented_dir=False
                    )

                    pbar.update(1)


def apply_radial_distortion(image: Image.Image, strength: float = 1.0
                            ) -> Image.Image:
    """
    Apply radial distortion effect to an image.

    :param image: PIL Image to apply the distortion
    :param strength: Strength of the radial distortion effect
    :return: Distorted image
    """
    width, height = image.size
    x_center, y_center = width / 2, height / 2
    new_image = Image.new("RGB", (width, height))

    for x in range(width):
        for y in range(height):
            x_diff = (x - x_center) ** 2
            y_diff = (y - y_center) ** 2
            denominator = 2 * x_center ** 2
            factor = 1 + strength * (x_diff + y_diff) / denominator
            new_x = int(x_center + (x - x_center) * factor)
            new_y = int(y_center + (y - y_center) * factor)
            if 0 <= new_x < width and 0 <= new_y < height:
                new_image.putpixel((x, y), image.getpixel((new_x, new_y)))

    return new_image


def apply_augmentations(file_path: str, save_to_augmented_dir: bool = False
                        ) -> None:
    """
    Apply various augmentations to an image and save results.

    :param file_path: Path to the image file to be augmented
    :param save_to_augmented_dir: Whether to save augmented images in a
                                  separate directory
    """
    original_image = Image.open(fp=file_path)
    base, extension = os.path.splitext(file_path)

    augmentations = {
        "_flip": ImageOps.mirror(image=original_image),
        "_rotate": original_image.rotate(angle=90, expand=True),
        "_blur": original_image.filter(filter=ImageFilter.BLUR),
        "_contrast": ImageOps.autocontrast(image=original_image),
        "_crop": original_image.crop(
            box=(
                original_image.width / 4, original_image.height / 4,
                3 * original_image.width / 4, 3 * original_image.height / 4
            )
        ),
        "_illuminate": ImageOps.solarize(image=original_image),
    }

    for suffix, img in augmentations.items():
        save_path_original = f'{base}{suffix}{extension}'
        img.save(fp=save_path_original)

        if save_to_augmented_dir:
            original_dir = os.path.dirname(file_path)
            parent_dir = os.path.dirname(original_dir)
            augmented_directory = os.path.join(
                parent_dir, 'augmented_directory',
                os.path.basename(original_dir)
            )
            os.makedirs(augmented_directory, exist_ok=True)
            save_path_augmented = os.path.join(
                augmented_directory,
                f'{os.path.basename(base)}{suffix}{extension}'
            )
            img.save(fp=save_path_augmented)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Apply various augmentations to an image."
    )
    parser.add_argument("file_path", type=str,
                        help="Path to the image file to be augmented")
    args = parser.parse_args()

    apply_augmentations(file_path=args.file_path, save_to_augmented_dir=True)
