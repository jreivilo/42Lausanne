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
    
    return X_train, X_test, y_train, y_test

def load_data():
    X_train = pd.read_csv('data/X_train.csv')
    y_train = pd.read_csv('data/y_train.csv')
    X_test = pd.read_csv('data/X_test.csv')
    y_test = pd.read_csv('data/y_test.csv')
    
    return X_train, X_test, y_train, y_test

def relu(x):
    return np.maximum(0, x)

def relu_derivative(x):
    return np.where(x > 0, 1, 0) #if x > 0 return 1, else return 0

def softmax(x):
    quotient = np.exp(x)
    div = np.sum(np.exp(x), axis=0)
    if div == 0:
        div = 1e-10

    result = quotient / div
    #check if result it nan and it there is one, replace it with 1 - the other value
    if np.isnan(result[0]) and np.isnan(result[1]):
        print("Nan value found 1")
        exit()
        result[0] = 0.5
        result[1] = 0.5
    
    if np.isnan(result[0]) or np.isnan(result[1]):
        print("Nan value found 2")
        exit()
        if np.isnan(result[0]):
            result[0] = 1 - result[1]
        if np.isnan(result[1]):
            result[1] = 1 - result[0]
    
    #check result, if the usm of the result is not 1 print and exit
    if np.sum(result).round(2) != 1:
        print(f"Sum of result: {np.sum(result)}")
        exit()
        
    return result
    
    # return np.exp(x) / np.sum(np.exp(x), axis=0)

def softmax_derivative(x):
    return x * (1 - x)


def forward_propagation(network, input_data):
    layer_outputs = [input_data]
    for i, layer in enumerate(network):
        weighted_sum = np.dot(layer_outputs[-1], layer['weights']) + layer['biases']
        if i == len(network) - 1:  # Last layer
            activation = softmax(weighted_sum)
        else:
            activation = relu(weighted_sum)
        layer_outputs.append(activation)
    return layer_outputs

def backpropagation(network, target, layer_outputs):
    target = np.array([1, 0]) if target == 1 else np.array([0, 1])

    deltas = []

    for i in reversed(range(len(network))):
        if i == len(network) - 1:
            delta = (layer_outputs[-1] - target) * softmax_derivative(layer_outputs[-1])
        else :
            delta = np.dot(deltas[-1], network[i + 1]['weights'].T) * relu_derivative(layer_outputs[i + 1])
        deltas.append(delta)
        
    #inverse the deltas
    deltas = deltas[::-1]
    gradients = []
    
    for i in range(len(network)):
        gradients.append({
            'weight_grad': np.dot(layer_outputs[i][:,None], deltas[i][:,None].T),
            'bias_grad': deltas[i]
        })
        
    return gradients
    

        
def validate_network(network, xval, yval):
    val_losses = []
    correct_predictions = 0

    for input_data, target in zip(xval, yval):
        output_layer = forward_propagation(network, input_data)[-1]
        # print(output_layer)
        target = np.array([1, 0]) if target == 1 else np.array([0, 1])
        loss = -np.sum(target * np.log(output_layer) + (1 - target) * np.log(1 - output_layer))
        val_losses.append(loss)

        # Count correct predictions for accuracy
        if np.argmax(output_layer) == np.argmax(target): #if the index of the max value in the output layer is the same as the index of the max value in the target
            correct_predictions += 1

    average_loss = np.mean(val_losses)
    accuracy = correct_predictions / len(xval)
    return average_loss, accuracy

def apply_gradients(network, batch_gradients, learning_rate):
    for i in range(len(network)):
        network[i]['weights'] -= learning_rate * batch_gradients[i]['weight_grad']
        network[i]['biases'] -= learning_rate * batch_gradients[i]['bias_grad']
    return network

def train_network(network, xtrain, ytrain, xval, yval, num_epochs, learning_rate, batch_size, early_stopping):
    # Convert to NumPy arrays
    xtrain = xtrain.values
    ytrain = ytrain.values
    xval = xval.values
    yval = yval.values
    
    training_data = list(zip(xtrain, ytrain)) #zip the input and target data together
    
    training_losses = []
    validation_losses = []
    training_accuracies = []  # Store training accuracies
    validation_accuracies = []
    
    for epoch in range(num_epochs):
        np.random.shuffle(training_data)
        batches = [training_data[k:k + batch_size] for k in range(0, len(training_data), batch_size)]

        #drop last batch if it is not the same size as the others
        if len(batches[-1]) != batch_size:
            batches.pop()

        for batch in batches:
            batch_gradients = [{'weight_grad': 0, 'bias_grad': 0} for _ in network]

            for input_data, target in batch:
                # Calculate gradients for each example in the batch
                layer_outputs = forward_propagation(network, input_data)
                gradients = backpropagation(network, target, layer_outputs)
                
                # print(gradients)
                for i, grad in enumerate(gradients):
                    batch_gradients[i]['weight_grad'] += grad['weight_grad']
                    batch_gradients[i]['bias_grad'] += grad['bias_grad']

            # Apply accumulated gradients after all batches are processed
            network = apply_gradients(network, batch_gradients, learning_rate) 
            # print("Battch gradients: ", batch_gradients)

        training_loss, training_accuracy = validate_network(network, xtrain, ytrain)
        training_losses.append(training_loss)
        training_accuracies.append(training_accuracy)  # Append training accuracy

        # Validation step
        val_loss, val_accuracy = validate_network(network, xval, yval)
        validation_losses.append(val_loss)
        validation_accuracies.append(val_accuracy)

        #implement early stopping 
        if epoch > early_stopping:
            if validation_losses[-1] > validation_losses[-(early_stopping + 1)]:
                print(f'Early stopping at epoch {epoch}')
                break

        print(f'Epoch {epoch+1}/{num_epochs}, Training Loss: {training_loss:.5f}, Validation Loss: {val_loss:.5f}, Training Accuracy: {training_accuracy:.5f}, Validation Accuracy: {val_accuracy:.5f}')
        
        #save training and validation losses to a csv file
        np.save('data/training_losses.npy', training_losses)
        np.save('data/validation_losses.npy', validation_losses)

    plot_graphs(training_losses, validation_losses, training_accuracies, validation_accuracies)
    
    #load training and validation losses
    training_losses = np.load('data/training_losses.npy')
    validation_losses = np.load('data/validation_losses.npy')

    return network

def print_model_architecture(layers, activation='relu', output_activation='softmax'):
    print("\nModel Architecture")
    print("----------------------------")
    print(f"{'Layer':<15}{'Output Shape':<20}{'Activation':<15}")
    print("----------------------------")
    for i, neurons in enumerate(layers):
        act = activation if i < len(layers) - 1 else output_activation
        print(f"{'Layer ' + str(i+1):<15}{str(neurons):<20}{act:<15}")
    print("----------------------------\n")


#main
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Train a multilayer perceptron")
    parser.add_argument('--layer', nargs='+', type=int, help='Number of neurons in each layer', required=True)
    parser.add_argument('--epochs', type=int, help='Number of epochs', required=True)
    parser.add_argument('--loss', type=str, help='Loss function', required=True)
    parser.add_argument('--batch_size', type=int, help='Batch size', required=True)
    parser.add_argument('--learning_rate', type=float, help='Learning rate', required=True)
    parser.add_argument('--early_stopping', type=int, help='Early stopping', required=False, default=parser.parse_args().epochs+1)

    args = parser.parse_args()
    print_args(args)

    network = create_network(args.layer)
    
    # X_train, X_val, y_train, y_val = split_data(df)
    X_train, X_val, y_train, y_val = load_data()
    
    print(f"Shape of X_train: {X_train.shape}")

    network = train_network(network, X_train, y_train, X_val, y_val, args.epochs, args.learning_rate, args.batch_size, args.early_stopping)
    
    #print model architexture in a pretty way
    print_model_architecture(args.layer)

    #save the model
    np.save('model.npy', network)
    
    