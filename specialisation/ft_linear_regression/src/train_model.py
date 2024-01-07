import os
import pandas as pd
import matplotlib.pyplot as plt

def estimate_price(km, theta0, theta1):
    return theta0 + (theta1 * km)

def standardize_data(dataset):
    return (dataset - dataset.mean()) / dataset.std()

def r_squared(dataset, theta0, theta1):
    sum_squared_errors = 0
    sum_squared_mean = 0
    mean = dataset['price'].mean()
    
    for km, price in dataset.itertuples(index=False):
        y_pred = estimate_price(km, theta0, theta1)
        sum_squared_errors += (price - y_pred) ** 2
        sum_squared_mean += (price - mean) ** 2
    
    return 1 - (sum_squared_errors / sum_squared_mean)

def update_theta(dataset, theta0, theta1, learning_rate):
    
    sum_errors_theta0 = 0
    sum_errors_theta1 = 0
    m = len(dataset)

    for km, price in dataset.itertuples(index=False):
        error = estimate_price(km, theta0, theta1) - price
        sum_errors_theta0 += error
        sum_errors_theta1 += error * km  # Fixed the error calculation for theta1
    
    tmp_theta0 = theta0 - learning_rate * (1 / m) * sum_errors_theta0
    tmp_theta1 = theta1 - learning_rate * (1 / m) * sum_errors_theta1
    
    # print(f"θ0 = {tmp_theta0}, θ1 = {tmp_theta1}")
    return tmp_theta0, tmp_theta1

def main():
    theta0 = 0
    theta1 = 0
    
    learning_rate = 0.01
    
    df = pd.read_csv("data/data.csv")
    df_std = standardize_data(df)
    
    
    # Number of iterations for gradient descent
    iterations = 1000  # Adjust as needed

    for _ in range(iterations):
        theta0, theta1 = update_theta(df_std[['km', 'price']], theta0, theta1, learning_rate)

    # Save the trained parameters
    with open("data/trained_parameters.txt", "w") as file:
        file.write(f"{theta0},{theta1}")

    print(f"Training complete. θ0 = {theta0}, θ1 = {theta1}")
    
    # calculate the r squared value
    r2 = r_squared(df_std, theta0, theta1)
    print(f"R² = {r2}")

    # Plotting the data and regression line
    plt.scatter(df['km'], df['price'], color='blue')  # Data points
    
    # Regression line on standardized data
    x = df_std['km']
    y = theta0 + theta1 * x
    
    # Convert standardized regression line to original scale
    x = df['km']
    y = y * df['price'].std() + df['price'].mean()
    
    # plot the regression line
    plt.plot(x, y, color='red')
    
    plt.xlabel('Normalized km')
    plt.ylabel('Price')
    plt.title('Linear Regression on Car Prices')
    
    #save the plot
    plt.savefig('plot/plot.png')

if __name__ == "__main__":
    main()
