import pandas as pd
import sys
import numpy as np

def calculate_statistics(data):
    # Initialize a dictionary to store statistics
    stats = {column: {'count': 0, 'mean': 0, 'std': 0, 'min': np.inf, '25%': 0, '50%': 0, '75%': 0, 'max': -np.inf} for column in data.columns}

    # Calculate count, mean, min, max
    for column in data.columns:
        count = 0
        total = 0
        for value in data[column]:
            count += 1
            total += value
            if value < stats[column]['min']:
                stats[column]['min'] = value
            if value > stats[column]['max']:
                stats[column]['max'] = value
        
        stats[column]['count'] = count
        stats[column]['mean'] = total / count

    # Calculate std
    for column in data.columns:
        variance_sum = 0
        for value in data[column]:
            variance_sum += (value - stats[column]['mean']) ** 2
        stats[column]['std'] = (variance_sum / stats[column]['count']) ** 0.5

    # Calculate percentiles
    for column in data.columns:
        sorted_values = sorted(data[column])
        stats[column]['25%'] = sorted_values[int(0.25 * (stats[column]['count'] - 1))]
        stats[column]['50%'] = sorted_values[int(0.50 * (stats[column]['count'] - 1))]
        stats[column]['75%'] = sorted_values[int(0.75 * (stats[column]['count'] - 1))]

    return stats

def describe_dataset(filename):
    try:
        # Load the dataset
        data = pd.read_csv(filename)

        # Filter out only numerical columns
        numerical_data = data.select_dtypes(include=['number'])

        # Calculate statistics
        stats = calculate_statistics(numerical_data)

        # Convert stats dictionary to DataFrame
        stats_df = pd.DataFrame(stats).T  # Transpose to get columns as rows
  
        return stats_df

    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python describe.py <filename>")
    else:
        result_df = describe_dataset(sys.argv[1])
        # inverse the dataframe
        result_df = result_df.T
        print(result_df)
