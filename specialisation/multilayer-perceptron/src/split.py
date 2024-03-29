import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import math
import argparse
from termcolor import colored, cprint
from network.create import create_network

from data_loader import load_data
from graph import plot_graphs
from utils import print_args

from sklearn.model_selection import train_test_split

def split_data(df):
    #upsample minority class
    df_majority = df[df.Target==1]
    df_minority = df[df.Target==0]
    
    df_minority_upsampled = df_minority.sample(n=len(df_majority), replace=True)
    df = pd.concat([df_majority, df_minority_upsampled])
    
    print(df['Target'].value_counts())
    
    X_train, X_test, y_train, y_test = train_test_split(df.drop('Target', axis=1), df['Target'], test_size=0.3, random_state=33)
    X_train = X_train.astype(np.float64)
    y_train = y_train.astype(np.float64)
    X_test = X_test.astype(np.float64)
    y_test = y_test.astype(np.float64)
    
    #save the data to a csv file
    X_train.to_csv('data/X_train.csv', index=False)
    y_train.to_csv('data/y_train.csv', index=False)
    X_test.to_csv('data/X_test.csv', index=False)
    y_test.to_csv('data/y_test.csv', index=False)
    
    return True

if __name__ == '__main__':
	parser = argparse.ArgumentParser(description='Train a neural network')
	parser.add_argument('--path', type=str, help='Path to the dataset', required=True)
	args = parser.parse_args()
	
	df = load_data(args.path)
	split_data(df)
	print('Data split successfully')