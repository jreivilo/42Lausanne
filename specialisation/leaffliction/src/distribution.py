import os
import sys
from collections import Counter
import matplotlib.pyplot as plt


def generate_charts(directory: str) -> None:
    """
    Generate pie and bar charts showing the distribution of plant types based
    on images in a directory.

    :param directory: Path to the directory containing plant images organized
                      by type
    """
    # Create a dictionary to hold the count of each plant type
    plant_type_counts = Counter()
    # Walk through the directory
    for root, dirs, files in os.walk(directory):
        # Save the first occurrence of root
        if root == directory:
            root_dir = root
        for file in files:
            if file.lower().endswith((
                '.png', '.jpg', '.jpeg', '.bmp', '.gif'
            )):
                # Increment the count of the plant type in the directory name
                plant_type = os.path.basename(root)
                plant_type_counts[plant_type] += 1

    plant_type, count = zip(*plant_type_counts.items())
    last_directory = os.path.basename(root_dir)

    # Define the output directory for charts
    output_dir = os.path.join("plot", "distribution", last_directory)
    # Create the directory if it doesn't
    os.makedirs(output_dir, exist_ok=True)

    # Now we have the counts for each plant type, we can generate charts
    # Generate pie chart
    labels = plant_type_counts.keys()
    sizes = plant_type_counts.values()
    fig1, ax1 = plt.subplots()
    ax1.pie(x=sizes, labels=labels, autopct='%1.1f%%')
    # Equal aspect ratio ensures that pie is drawn as circle.
    ax1.axis('equal')
    plt.title(label=f'{last_directory} class distribution')
    plt.savefig(os.path.join(output_dir, f"{last_directory}_pie_chart.png"))

    # Generate bar chart
    fig2, ax2 = plt.subplots()
    ax2.bar(x=labels, height=sizes)
    plt.title(label=f'{last_directory} class distribution')
    plt.xlabel(xlabel='Plant Type')
    plt.ylabel(ylabel='Count')
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, f"{last_directory}_bar_chart.png"))


if __name__ == "__main__":
    # Take the directory from the command line arguments
    if len(sys.argv) != 2:
        print("Usage: ./Distribution.py <directory>")
        sys.exit(1)
    directory = sys.argv[1]
    # Create plot directory if it does not exist
    if not os.path.exists(path='plot'):
        os.makedirs(name='plot')
    generate_charts(directory=directory)
