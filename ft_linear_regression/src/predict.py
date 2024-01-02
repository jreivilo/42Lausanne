# predict.py
import os
import pandas as pd

def estimate_price(mileage, theta0, theta1):
    return theta0 + (theta1 * mileage)

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

	while True:
		user_input = input("Enter the mileage of the car: ")

		try:
			mileage = float(user_input)

			if mileage < 0:
				print("Mileage cannot be negative. Please enter a valid positive number.")
			else:
				# Standardize user input
				mileage_std = (mileage - df['km'].mean()) / df['km'].std()
    
				price_std = estimate_price(mileage_std, theta0, theta1)

				# Convert standardized value to actual value
				price = price_std * df['price'].std() + df['price'].mean()
    
				print(f"Estimated price for a car with {mileage} miles is: ${price:.2f}")
				break

		except ValueError:
			print(f"Invalid input '{user_input}'. Please enter a valid number.")

if __name__ == "__main__":
	main()
