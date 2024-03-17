# ANSI escape sequences for color
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import math
import argparse
from termcolor import colored, cprint
from network.create import create_network

from data_loader import load_data
from graph import plot_graphs

from sklearn.model_selection import train_test_split


class Color:
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    CYAN = '\033[96m'
    RESET = '\033[0m'

def print_color(text, color):
    print(color + text + Color.RESET)


def print_args(args: argparse.Namespace):
    cprint("Arguments", "green")
    print("Number of layers: ", len(args.layer))
    print("Number of epochs: ", args.epochs)
    print("Loss function: ", args.loss)
    print("Batch size: ", args.batch_size)
    print("Learning rate: ", args.learning_rate)
    print("\n")