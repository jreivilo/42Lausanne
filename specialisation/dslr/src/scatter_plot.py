import pandas as pd
import numpy as np
import sys
import matplotlib.pyplot as plt
import itertools

def plot_scatter(subplot, data, feature1, feature2):
    """
    Plot a scatter plot for two features on a given subplot.
    """
    subplot.scatter(data[feature1], data[feature2], alpha=0.5)
    subplot.set_title(f"{feature1} vs {feature2}")
    subplot.set_xlabel(feature1)
    subplot.set_ylabel(feature2)

def get_top_correlations(data, n=6):
    """
    Returns the top n pairs of features with the highest absolute correlation.
    """
    corr_matrix = data.corr().abs()
    sorted_pairs = corr_matrix.unstack().sort_values(kind="quicksort", ascending=False)
    return sorted_pairs[sorted_pairs < 1].drop_duplicates().head(n)

def main(df_path):
    # Load the data into a pandas DataFrame
    try:
        data = pd.read_csv(df_path)
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
    course_data = data[course_columns]

    # Get the top 6 pairs of features with the highest correlation
    top_pairs = get_top_correlations(course_data, 6)

    # Create a figure with subplots for top pairs
    fig, axs = plt.subplots(nrows=3, ncols=2, figsize=(10, 15))

    # Iterate over each pair of features and plot a scatter plot
    for i, ((feature1, feature2), _) in enumerate(top_pairs.items()):
        plot_scatter(axs[i//2, i%2], course_data, feature1, feature2)


    # Adjust layout to prevent overlapping
    plt.tight_layout()

    # Show the figure
    plt.show()

    # Print the most similar pair of features
    most_similar_pair = top_pairs.idxmax()
    print(f"The two most similar features are: {most_similar_pair[0]} and {most_similar_pair[1]}")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        main(sys.argv[1])
    else:
        print("Please provide the path to the DataFrame as an argument.")
