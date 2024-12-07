from plantcv import plantcv as pcv
import matplotlib.pyplot as plt
import altair as alt
import os
import numpy as np
import cv2
import argparse


def convert_to_grayscale(original_image: np.ndarray) -> np.ndarray:
    """
    Convert an RGB image to grayscale.

    :param original_image: Original RGB image
    :return: Grayscale image
    """
    gray_image = pcv.rgb2gray(rgb_img=original_image)
    return gray_image


def thresholding_for_leaf_shape(gray_image: np.ndarray) -> np.ndarray:
    """
    Apply binary thresholding to isolate the leaf shape in a grayscale image.

    :param gray_image: Grayscale image
    :return: Binary image highlighting the leaf shape
    """
    binary_image = pcv.threshold.binary(
        gray_img=gray_image, threshold=120, object_type='light'
    )
    binary_image = pcv.invert(gray_img=binary_image)
    return binary_image


def extract_leaf_shape(
    original_image: np.ndarray, binary_image: np.ndarray
) -> np.ndarray:
    """
    Apply a mask to the original image to isolate the leaf shape.

    :param original_image: Original RGB image
    :param binary_image: Binary image of the leaf shape
    :return: Masked image of the leaf shape
    """
    leaf_shape = pcv.apply_mask(
        img=original_image, mask=binary_image, mask_color='white'
    )
    return leaf_shape


def add_leaf_image_green_to_original_image(
    original_image: np.ndarray, leaf_image: np.ndarray
) -> np.ndarray:
    """
    Add the leaf shape with a green background to the original image.

    :param original_image: Original RGB image
    :param leaf_image: Masked leaf shape image
    :return: Image with green background on the leaf shape area
    """
    leaf_image = pcv.rgb2gray(rgb_img=leaf_image)
    leaf_image = pcv.threshold.binary(
        gray_img=leaf_image, threshold=120, object_type='light'
    )
    leaf_image = pcv.apply_mask(
        img=original_image, mask=leaf_image, mask_color='white'
    )
    white_color = [255, 255, 255]
    green_color = [0, 255, 0]
    white_pixels = np.where((leaf_image == white_color).all(axis=2))
    leaf_image[white_pixels] = green_color
    return leaf_image


def analyse_leaf_shape(
    original_image: np.ndarray, mask: np.ndarray
) -> np.ndarray:
    """
    Analyze the leaf shape.

    :param original_image: Original RGB image
    :param mask: Masked leaf shape
    :return: Image with leaf shape analysis
    """
    analysis_image = pcv.analyze.size(
        img=original_image, labeled_mask=mask, n_labels=1
    )
    return analysis_image


def acute_marking(
    original_image: np.ndarray, mask: np.ndarray
) -> np.ndarray:
    """
    Mark the acute angles in the leaf shape.

    :param original_image: Original RGB image
    :param mask: Masked leaf shape
    :return: Image with marked acute angles
    """
    print(f"Shape of original image: {original_image.shape}")
    print(f"Shape of mask: {mask.shape}")
    acute_image = pcv.homology.acute(
        img=original_image, mask=mask, win=5, threshold=180
    )
    return acute_image


def historgam_pixel_intensity(
    original_image: np.ndarray, mask: np.ndarray
):
    """
    Generate a histogram of pixel intensity.

    :param original_image: Original RGB image
    :param mask: Masked leaf shape
    :return: Figure and data for pixel intensity histogram
    """
    pcv.params.debug = "plot"
    hist_figure, hist_data = pcv.visualize.histogram(
        img=original_image, hist_data=True
    )
    return hist_figure, hist_data


def save_transformation_results(
    base_output_path: str, transformations: dict
) -> None:
    """
    Save transformation results to the specified output path.

    :param base_output_path: Base output directory path
    :param transformations: Dictionary of transformation results
    """
    os.makedirs(base_output_path, exist_ok=True)
    for name, image in transformations.items():
        save_path = os.path.join(base_output_path, f"{name}.png")

        if isinstance(image, plt.Figure):  # For matplotlib figures
            image.savefig(fname=save_path)
        elif isinstance(image, np.ndarray):  # For OpenCV images (numpy array)
            cv2.imwrite(filename=save_path, img=image)
        elif isinstance(image, alt.Chart):  # For Altair charts
            image.save(fp=save_path)  # Save based on `save_path` extension
        else:
            print(f"Skipping unsupported format for {name}")


def apply_transformations(
    image_path: str, base_output_dir: str = "plot/transformation"
) -> None:
    """
    Apply transformations to an image and save results.

    :param image_path: Path to the input image
    :param base_output_dir: Base directory for saving transformation results
    """
    pcv.params.debug = "none"
    print(f"Processing image: {os.path.basename(image_path)}")

    original_image = cv2.imread(filename=image_path)
    image_type = os.path.basename(os.path.dirname(image_path))
    image_name = os.path.splitext(os.path.basename(image_path))[0]
    output_dir = os.path.join(base_output_dir, image_type, image_name)
    os.makedirs(output_dir, exist_ok=True)

    # Perform transformations
    gray_image = convert_to_grayscale(original_image=original_image)
    binary_image = thresholding_for_leaf_shape(gray_image=gray_image)
    leaf_image = extract_leaf_shape(
        original_image=original_image, binary_image=binary_image
    )
    leaf_shape_green_background = add_leaf_image_green_to_original_image(
        original_image=original_image, leaf_image=leaf_image
    )
    leaf_shape_analysis = analyse_leaf_shape(
        original_image=original_image, mask=binary_image
    )
    edges = pcv.canny_edge_detect(img=original_image)
    hist_figure, _ = historgam_pixel_intensity(
        original_image=original_image, mask=binary_image
    )

    # Organize transformations into a dictionary
    transformations = {
        "gray_image": gray_image,
        "binary_image": binary_image,
        "leaf_image": leaf_image,
        "leaf_shape_green_background": leaf_shape_green_background,
        "leaf_shape_analysis": leaf_shape_analysis,
        "edges": edges,
        "histogram": hist_figure
    }

    # Save transformations to the specified output directory
    save_transformation_results(
        base_output_path=output_dir, transformations=transformations
    )


def main(
    input_path: str, base_output_dir: str = "plot/transformation"
) -> None:
    """
    Main function to apply transformations on an image or directory of images.

    :param input_path: Path to the input image or directory
    :param base_output_dir: Base directory for saving transformation results
    """
    if os.path.isfile(input_path):
        apply_transformations(
            image_path=input_path, base_output_dir=base_output_dir
        )
    elif os.path.isdir(input_path):
        for root, _, files in os.walk(input_path):
            for file in files:
                if file.lower().endswith(('.png', '.jpg', '.jpeg')):
                    image_path = os.path.join(root, file)
                    apply_transformations(
                        image_path=image_path, base_output_dir=base_output_dir
                    )
    else:
        print(f"The path {input_path} does not exist.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Apply various augmentations to an image or directory of "
                    "images."
    )
    parser.add_argument(
        "input_path", type=str,
        help="Path to the image file or directory of images to be transformed."
    )
    parser.add_argument(
        "-o", "--output_dir", type=str,
        help="Directory to save transformed images if input is a directory."
    )
    args = parser.parse_args()

    output_dir = args.output_dir if args.output_dir else "plot/transformation"
    main(input_path=args.input_path, base_output_dir=output_dir)
