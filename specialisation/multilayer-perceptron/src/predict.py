import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import math
import argparse
from termcolor import colored, cprint
from network.create import create_network

from graph import plot_graphs
from utils import print_args

from sklearn.model_selection import train_test_split

from train import softmax, forward_propagation


if __name__ == "__main__":
	#load model saved as model.npy
	model = np.load('model.npy', allow_pickle=True)

	#pred on data/X_test.csv
	X_test = pd.read_csv('data/X_test.csv').values	
	y_test = pd.read_csv('data/y_test.csv').values

	sum_loss = 0
	for input_data, target in zip(X_test, y_test):
		outputs = forward_propagation(model, input_data)[-1]
		target = np.array([1, 0]) if target == 1 else np.array([0, 1])
		#calculate binary cross entropy loss
		loss = target * np.log(outputs) + (1 - target) * np.log(1 - outputs)
		sum_loss += loss
	
	#calculate average loss
	avg_loss = -sum_loss / len(X_test)
	print(f"Binary Cross Entropy Loss: {avg_loss[0]}")

