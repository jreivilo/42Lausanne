import sys
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt

def main(df_path):
	# Load the data
	try:
		data = pd.read_csv(df_path)
	except Exception as e:
		print(f"An error occurred while reading the file: {e}")
		return

	features = [col for col in data.columns if col not in ['Index', 'First Name', 'Last Name']]
	print(features)

	# Generate a pair plot
	sns.pairplot(data[features], hue='Hogwarts House', diag_kind='hist', corner=True)
	
	#save the plot
	plt.savefig('plot/pair_plot.png')
	plt.show()

if __name__ == "__main__":
    if len(sys.argv) > 1:
        main(sys.argv[1])
    else:
        print("Please provide the path to the DataFrame as an argument.")
