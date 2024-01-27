import os
import sys
from collections import Counter
import matplotlib.pyplot as plt
from PIL import Image

def generate_charts(directory):
    # Create a dictionary to hold the count of each plant type
    plant_type_counts = Counter()
    # Walk through the directory
    for root, dirs, files in os.walk(directory):
        #save the first occurence of root
        if root == directory:
            root_dir = root
        for file in files:
            if file.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp', '.gif')):
                # Increment the count of the plant type in the directory name
                plant_type = os.path.basename(root)
                plant_type_counts[plant_type] += 1

    plant_type, count = zip(*plant_type_counts.items())
    last_directory = os.path.basename(root_dir)
    # Now we have the counts for each plant type, we can generate charts
    # Generate pie chart
    labels = plant_type_counts.keys()
    sizes = plant_type_counts.values()
    fig1, ax1 = plt.subplots()
    ax1.pie(sizes, labels=labels, autopct='%1.1f%%')
    ax1.axis('equal')  # Equal aspect ratio ensures that pie is drawn as a circle.
    plt.title(f'{last_directory} class distribution')
    plt.savefig(f'plot/{last_directory}_pie_chart.png')
        
    # Generate bar chart
    fig2, ax2 = plt.subplots()
    ax2.bar(labels, sizes)
    plt.title(f'{plant_type} class distribution')
    plt.xlabel('Plant Type')
    plt.ylabel('Count')
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.savefig(f'plot/{last_directory}_bar_chart.png')
        
    # print("Charts have been generated.")


if __name__ == "__main__":
    # Take the directory from the command line arguments
    if len(sys.argv) != 2:
        print("Usage: ./Distribution.py <directory>")
        sys.exit(1)
    directory = sys.argv[1]
    generate_charts(directory)