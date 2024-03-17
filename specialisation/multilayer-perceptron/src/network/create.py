import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import math
import argparse

def create_network(layers: list) -> list:
	if len(layers) < 2:
		raise ValueError("Network should have at least two layers (input and output)")

	#add input (30) and output (2) layers
	layers.insert(0, 30)
	layers.append(2)

	np.random.seed(193)
	network = []
	for i in range(len(layers) - 1):
		# Xavier initialization for weights
		init_scale = np.sqrt(2. / (layers[i] + layers[i+1]))
		layer = {
			'weights': np.random.randn(layers[i], layers[i+1]) * init_scale,
			'biases': np.random.randn(layers[i+1]) * init_scale
		}
		network.append(layer)
		
		# Print the number of weights and biases per layer
		print(f"Layer {i+1}:")
		print(f"Number of weights: {len(layer['weights'])}")
		print(f"Number of biases: {layers[i+1]}")
		print()

	print(network)
	return network
