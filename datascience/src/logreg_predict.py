import sys
import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler

def load_data(filename):
    try:
        data = pd.read_csv(filename)
        return data
    except Exception as e:
        print(f"An error occurred: {e}")
        return None

def softmax(z):
    exp = np.exp(z - np.max(z))
    return exp / exp.sum(axis=1, keepdims=True)

def preprocess_data(data):
    features = [col for col in data.columns if col not in ['Index', 'First Name', 'Last Name', 'Hogwarts House', 'Birthday']]
    print(f"Features: {features}")
    data['Best Hand'] = data['Best Hand'].map({'Right': 1, 'Left': 0})
    data.fillna(data.mean(), inplace=True)
    
    scaler = StandardScaler()
    scaler.fit(data[features])
    data[features] = scaler.transform(data[features])
    return data[features]

def predict_houses(test_data, weights):
    X_test = test_data.values
    logits = np.dot(X_test, weights)
    y_pred = softmax(logits)
    predictions = np.argmax(y_pred, axis=1)
    return predictions

def map_predictions_to_houses(predictions):
    houses = ['Gryffindor', 'Hufflepuff', 'Ravenclaw', 'Slytherin']
    return [houses[p] for p in predictions]

def main(test_file, weights_file):
	test = load_data(test_file)
	weights = np.load(weights_file)

	test = preprocess_data(test)
	predictions = predict_houses(test, weights)
	predictions = map_predictions_to_houses(predictions)
 
	#add Index
	predictions = [[i+1, predictions[i]] for i in range(len(predictions))]
	#add column name to Index and Hogwarts House
	predictions = [['Index', 'Hogwarts House']] + predictions
	
	#save predictions in /resources/houses.csv
	pd.DataFrame(predictions).to_csv('results/houses.csv', header=False, index=False)
	

if __name__ == "__main__":
    if len(sys.argv) > 2:
        main(sys.argv[1], sys.argv[2])
    else:
        print("Please provide two arguments: test.csv and weights.npy")
