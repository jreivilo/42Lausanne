import numpy as np
import mne
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split, cross_val_score, StratifiedKFold
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score, make_scorer
from sklearn.pipeline import make_pipeline
from sklearn.base import BaseEstimator, TransformerMixin
from mne.decoding import CSP
import argparse
from joblib import dump

from csp import CustomCSP

#import lgmbclassifier
from lightgbm import LGBMClassifier

#import svm omdel
from sklearn.svm import SVC

BASELINE = [1, 2]
TASK_1 = [3, 7, 11]
TASK_2 = [4, 8, 12]
TASK_3 = [5, 9, 13]
TASK_4 = [6, 10, 14]

task_numbers = {
	1: TASK_1,
	2: TASK_2,
	3: TASK_3,
	4: TASK_4
}

accuracy_task_1 = -1
accuracy_task_2 = -1
accuracy_task_3 = -1
accuracy_task_4 = -1

tmin = -0.5
tmax = 4.5

event_id = dict(T1=2, T2=3)

DATA_PATH = 'data/physionet.org/files/eegmmidb/1.0.0/'

SUBJECT = 1

def get_file_names_control(subject, task_number, control=False):
	subject = f"S{subject:03d}"
	print(f"Loading data for subject {subject}")

	task = task_numbers[task_number]
	if control:
		task = [task[-1]] # only load the last task
	else:
		task = task[:-1]

	file_names = [f"{subject}/{subject}R{task_number:02d}.edf" for task_number in task]
	print(f"File names: {file_names}")
	return file_names

def get_file_names(subject, task_number, control=False):
    subject = f"S{subject:03d}"
    print(f"Loading data for subject {subject}")

    task = task_numbers[task_number]
    
    file_names = [f"{subject}/{subject}R{task_number:02d}.edf" for task_number in task]
    print(f"File names: {file_names}")
    return file_names

def create_pipeline():
    csp = CustomCSP(n_components=32, reg='empirical', log=True)
    # lgbm = LGBMClassifier()
    # lr = LogisticRegression(random_state=42)
    svm = SVC(kernel='linear', C=1, random_state=42)
    pipeline = make_pipeline(csp, svm)
    return pipeline

def load_epoch_data(task, subjects):
	files = []
	epochs_data = []
	for subject in subjects:
		files.extend(get_file_names(subject, task))

	for file_name in files:
		# Load the data
		raw = mne.io.read_raw_edf(DATA_PATH + file_name, preload=True, verbose=False)
		raw.filter(7., 30., fir_design='firwin', skip_by_annotation='edge', verbose=False)

		events, all_event_id = mne.events_from_annotations(raw)
		picks = mne.pick_types(raw.info, eeg=True, eog=False, stim=False, exclude='bads')
		epochs = mne.Epochs(raw, events, event_id, tmin, tmax, proj=True, picks=picks, baseline=None, preload=True, verbose=False)

		#store the data in the list
		epochs_data.append(epochs)

	epochs = mne.concatenate_epochs(epochs_data, verbose=False)
	return epochs
  
def load_epoch_data_control(task, control=False):
	files = []
	epochs_data = []
	subjects = list(range(1, 110))
	subjects.remove(88) #wrong fs_freq
	subjects.remove(92) #wrong fs_freq
	subjects.remove(100) #wrong fs_freq
 
	for subject in subjects:
		files.extend(get_file_names_control(subject, task, control))
	for file_name in files:
		# Load the data
		raw = mne.io.read_raw_edf(DATA_PATH + file_name, preload=True, verbose=False)
		raw.filter(7., 30., fir_design='firwin', skip_by_annotation='edge', verbose=False)

		events, all_event_id = mne.events_from_annotations(raw)
		picks = mne.pick_types(raw.info, eeg=True, eog=False, stim=False, exclude='bads')
		epochs = mne.Epochs(raw, events, event_id, tmin, tmax, proj=True, picks=picks, baseline=None, preload=True, verbose=False)

		#store the data in the list
		epochs_data.append(epochs)
    
	epochs = mne.concatenate_epochs(epochs_data, verbose=False)
	return epochs
    

def main():
    #dont pick subject 88 92 100
	train_subjects = range(1, 88)
	test_subjects = [89, 90, 91, 93, 94, 95, 96, 97, 98, 99, 101, 102, 103, 104, 105, 106, 107, 108, 109]

	train_files = []
	test_files = []

	for task in task_numbers:
		print(f"Training for task {task}")
		epochs = load_epoch_data_control(task, control=False)
  
		pipe = create_pipeline()
		pipe.fit(epochs.get_data(), epochs.events[:, -1])

		epochs = load_epoch_data_control(task, control=True)
		predictions = pipe.predict(epochs.get_data())
		truth = epochs.events[:, -1]
		accuracy = accuracy_score(truth, predictions)

		if task == 1:
			accuracy_task_1 = accuracy
		elif task == 2:
			accuracy_task_2 = accuracy
		elif task == 3:
			accuracy_task_3 = accuracy
		elif task == 4:
			accuracy_task_4 = accuracy
	
	print(f"Accuracy for task 1: {accuracy_task_1}")
	print(f"Accuracy for task 2: {accuracy_task_2}")
	print(f"Accuracy for task 3: {accuracy_task_3}")
	print(f"Accuracy for task 4: {accuracy_task_4}")
 
	mean_accuracy = (accuracy_task_1 + accuracy_task_2 + accuracy_task_3 + accuracy_task_4) / 4
	print(f"Mean accuracy: {mean_accuracy}")

	
 
 
if __name__ == "__main__":
    main()

