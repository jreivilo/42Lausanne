import pandas as pd
import numpy as np
import sys
import matplotlib.pyplot as plt

def main(df_path):
    # Load the data into a pandas DataFrame
    try:
        data = pd.read_csv(df_path)
        # print(data.head())
    except Exception as e:
        print(f"An error occurred: {e}")
        return

    # Select columns related to courses
    course_columns = [
        'Arithmancy', 'Astronomy', 'Herbology', 'Defense Against the Dark Arts',
        'Divination', 'Muggle Studies', 'Ancient Runes', 'History of Magic',
        'Transfiguration', 'Potions', 'Care of Magical Creatures', 'Charms', 'Flying'
    ]

    # Filter the DataFrame to include only the relevant columns
    course_data = data[['Hogwarts House'] + course_columns]

    # Assume course_data is your DataFrame

    # Calculate the number of rows and columns for subplots
    num_columns = len(course_data.columns) - 1  # excluding 'Hogwarts House'
    ncols = int(np.ceil(np.sqrt(num_columns)))
    nrows = int(np.ceil(num_columns / ncols))

    # Create a figure
    plt.figure(figsize=(15, 10)) # Adjust the size as needed

    # Iterate over each column and add a subplot
    for i, column in enumerate(course_data.columns):
        if column == 'Hogwarts House':
            continue  # Skip the 'Hogwarts House' column

        # Add a subplot in the i-th position (1-indexed)
        plt.subplot(nrows, ncols, i + 1)

        # Plot the histogram for each Hogwarts House
        for house in ['Gryffindor', 'Slytherin', 'Hufflepuff', 'Ravenclaw']:
            house_data = course_data[course_data['Hogwarts House'] == house]
            plt.hist(house_data[column], alpha=0.5, label=house, bins=10)

        # Set the title, labels, and legend
        plt.title(f"Histogram of {column} by House")
        plt.xlabel(column)
        plt.ylabel("Frequency")
        plt.legend()

    # Adjust layout to prevent overlapping
    plt.tight_layout()

    # Show the figure
    plt.show()


    # Calculate the variance of the scores for each course for each house
    variances = course_data.groupby('Hogwarts House').var()
    print(variances)

    # Calculate the average variance across houses for each course
    average_variances = variances.mean(axis=0)
    rounded_values = round(average_variances, 2).astype(float)
    print(rounded_values)

    
    # Find the course with the lowest average variance
    homogeneous_course = average_variances.idxmin()

    # Print the result
    print(f"The course with the most homogeneous score distribution between all four houses is: {homogeneous_course}")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        main(sys.argv[1])
    else:
        print("Please provide the path to the DataFrame as an argument.")
