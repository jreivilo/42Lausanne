from plantcv import plantcv as pcv
import matplotlib.pyplot as plt
import math
import numpy as np
import cv2
import argparse

def convert_to_grayscale(original_image):
    gray_image = pcv.rgb2gray(original_image)
    return gray_image

def thresholding_for_leaf_shape(gray_image):
    # Apply binary thresholding
    binary_image = pcv.threshold.binary(gray_image, 120, 'light')
    #invert the binary image
    binary_image = pcv.invert(binary_image)
    return binary_image

def extract_leaf_shape(original_image, binary_image):
    # Apply the mask to isolate the leaf
    leaf_shape = pcv.apply_mask(original_image, binary_image, 'white')
    return leaf_shape

def add_leaf_image_green_to_original_image(original_image, leaf_image):
    #leaf image to binary
    leaf_image = pcv.rgb2gray(leaf_image)
    leaf_image = pcv.threshold.binary(leaf_image, 120, 'light')
    
    leaf_image = pcv.apply_mask(original_image, leaf_image, 'white')
    #white pixels to green
    leaf_image[np.where((leaf_image==[255,255,255]).all(axis=2))] = [0,255,0]
    return leaf_image

def analyse_leaf_shape(original_image, mask):
    # Analyse the leaf shape
    analysis_image = pcv.analyze.size(img=original_image, labeled_mask=mask, n_labels=1)
    return analysis_image

def acute_marking(original_image, mask):
    # Mark the acute angles
    print(f"Shape of original image: {original_image.shape}")
    print(f"Shape of mask: {mask.shape}")
    acute_image = pcv.homology.acute(img=original_image, mask=mask, win=5, threshold=180)
    return acute_image

def historgam_pixel_intensity(original_image, mask):
    # Histogram of pixel intensity
    pcv.params.debug = "plot"
    hist_figure, hist_data = pcv.visualize.histogram(img=original_image, hist_data=True)
    return hist_figure, hist_data
    
    

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="Apply various augmentations to an image.")
	parser.add_argument("file_path", type=str, help="Path to the image file to be augmented")
	args = parser.parse_args()

	file_path = args.file_path
	original_image = cv2.imread(file_path)

	gray_image = convert_to_grayscale(original_image)
	cv2.imwrite('plot/transformation/gray_image.png', gray_image)

	binary_image = thresholding_for_leaf_shape(gray_image)
	cv2.imwrite('plot/transformation/binary_image.png', binary_image)

	leaf_image = extract_leaf_shape(original_image, binary_image)
	cv2.imwrite('plot/transformation/leaf_image.png', leaf_image)

	leaf_shape_green_background = add_leaf_image_green_to_original_image(original_image, leaf_image)
	cv2.imwrite('plot/transformation/leaf_shape_green_background.png', leaf_shape_green_background)

	leaf_shape_analysis = analyse_leaf_shape(original_image, binary_image)
	cv2.imwrite('plot/transformation/leaf_shape_analysis.png', leaf_shape_analysis)

	# leaf_marked_image = acute_marking(original_image, binary_image)
	# # pcv.plot_image(leaf_marked_image, title="Leaf Marked Image")

	edges = pcv.canny_edge_detect(original_image)
	cv2.imwrite('plot/transformation/edges.png', edges)


	hist_figure, hist_data = historgam_pixel_intensity(original_image, binary_image)
	hist_figure.save('plot/transformation/hist_figure.png')
	# np.savetxt("plot/transformation/hist_data.csv", hist_data, delimiter=",")
