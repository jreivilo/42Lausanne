import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import math
import argparse
from termcolor import colored, cprint

from network.create import create_network

from sklearn.model_selection import train_test_split

#import standardscaler
from sklearn.preprocessing import StandardScaler, RobustScaler, MinMaxScaler

def load_data(path):
    df = pd.read_csv(path)
    column_names = ['Index', 'Target'] + [f'Attribute_{i}' for i in range(1, len(df.columns) - 1)]
    df.columns = column_names
    df.drop('Index', axis=1, inplace=True)
    
    #process target column, 1 for B 0 for M
    df['Target'] = df['Target'].map({'B': 1, 'M': 0})
    
	# Normalize and standardize data 0 and 1
    scaler = RobustScaler()
    df.iloc[:, 1:] = scaler.fit_transform(df.iloc[:, 1:])
    scaler = MinMaxScaler()
    df.iloc[:, 1:] = scaler.fit_transform(df.iloc[:, 1:])
    
    
    #print number of target classes
    cprint(df['Target'].value_counts(), 'yellow')
        
    #summary statistics
    # print(df.describe())

    return df