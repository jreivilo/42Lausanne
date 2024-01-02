import os
import pandas as pd	

def estimate_price(km, theta0, theta1):
    return theta0 + (theta1 * km)

def r_squared(dataset, theta0, theta1):
    sum_squared_errors = 0
    sum_squared_mean = 0
    mean = dataset['price'].mean()
    
    for km, price in dataset.itertuples(index=False):
        y_pred = estimate_price(km, theta0, theta1)
        sum_squared_errors += (price - y_pred) ** 2
        sum_squared_mean += (price - mean) ** 2
    
    return 1 - (sum_squared_errors / sum_squared_mean)

def standardize_data(dataset):
    return (dataset - dataset.mean()) / dataset.std()

def main():
	# Initial values for theta0 and theta1
	theta0 = 0
	theta1 = 0
	df = pd.read_csv("data/data.csv")

	if not os.path.isfile("data/trained_parameters.txt"):
		print("Trained parameters not found. Please train the model first.")
		return
	else :
		with open("data/trained_parameters.txt", "r") as file:
			theta0, theta1 = file.read().split(",")
			theta0 = float(theta0)
			theta1 = float(theta1)

	df = pd.read_csv("data/data.csv")

	# Standardize the data
	df_std = standardize_data(df)

	# Calculate the R-squared value
	r2 = r_squared(df_std, theta0, theta1)

	print(f"R² = {r2}")

if __name__ == "__main__":
	main()
 
