import sys
import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline

def load_data(filename):
	try:
		data = pd.read_csv(filename)
		return data
	except Exception as e:
		print(f"An error occurred: {e}")

def softmax(z):
    exp = np.exp(z - np.max(z))
    return exp / exp.sum(axis=1, keepdims=True)

def cross_entropy_loss(y_true, y_pred):
    # Assuming y_true is one-hot encoded
    loss = -np.sum(y_true * np.log(y_pred + 1e-15)) / y_true.shape[0] # 1e-15 is added to avoid 0 in the log
    return loss

def initialize_parameters(n_features, n_classes):
    weights = np.random.randn(n_features, n_classes) * 0.01
    print(weights)
    bias = np.zeros((1, n_classes))
    print(bias)
    return weights, bias

def compute_gradients(X, y_true, y_pred, weights, lambda_reg=0.01): #lambda_reg is the regularization parameter
    m = X.shape[0]
    dw = (np.dot(X.T, (y_pred - y_true)) + lambda_reg * weights) / m
    db = np.sum(y_pred - y_true, axis=0, keepdims=True) / m
    return dw, db

def train_logistic_regression(X_train, y_train, n_classes, learning_rate, n_iterations):
    n_features = X_train.shape[1]
    weights, bias = initialize_parameters(n_features, n_classes)

    for i in range(n_iterations):
        logits = np.dot(X_train, weights)
        y_pred = softmax(logits)

        # Compute the loss
        loss = cross_entropy_loss(y_train, y_pred)

        # Compute gradients
        dw, db = compute_gradients(X_train, y_train, y_pred, weights)

        # Update parameters
        weights -= learning_rate * dw
        bias -= learning_rate * db

        if i % 100 == 0:
            print(f"Iteration {i}: Loss {loss}")

    return weights, bias

def main(train, test):
    features = [col for col in train.columns if col not in ['Index', 'First Name', 'Last Name', 'Hogwarts House', 'Birthday']]
    
    #column Best Hand as boolean
    train['Best Hand'] = train['Best Hand'].map({'Right': 1, 'Left': 0})
    test['Best Hand'] = test['Best Hand'].map({'Right': 1, 'Left': 0})
    
    #count number of missing values
    print(train.isnull().sum())
    print(test.isnull().sum())
    
    #fill missing values with mean
    train.fillna(train.mean(), inplace=True)
    test.fillna(test.mean(), inplace=True)
    
    print(train.isnull().sum())
    print(test.isnull().sum())
    
    #standardize data
    scaler = StandardScaler()
    scaler.fit(train[features])
    train[features] = scaler.transform(train[features])
    test[features] = scaler.transform(test[features])
    
    X_train = train[features].values
    y_train = pd.get_dummies(train['Hogwarts House']).values
    X_test = test[features].values

    weights, bias = train_logistic_regression(X_train, y_train, n_classes=4, learning_rate=0.01, n_iterations=10000)
    
    #save model
    np.save('model/weights.npy', weights)
    
    #print accuracy on train set
    logits = np.dot(X_train, weights)
    y_pred = softmax(logits)
    y_pred = np.argmax(y_pred, axis=1)
    y_true = np.argmax(y_train, axis=1)
    print(f"Accuracy on train set: {np.mean(y_pred == y_true)}")


if __name__ == "__main__":
	if len(sys.argv) > 2:
		try :
			train = load_data(sys.argv[1])
			print(train.head())
			test = load_data(sys.argv[2])
			print(test.head())
		except Exception as e:
			print(f"An error occurred: {e}")

		main(train, test)
	else:
		print("Please provide two arguments: train.csv and test.csv")