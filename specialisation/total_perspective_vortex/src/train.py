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


BASELINE = [1, 2]
TASK_1 = [3, 7, 11]
TASK_2 = [4, 8, 12]
TASK_3 = [5, 9, 13]
TASK_4 = [6, 10, 14]

tmin = -0.5
tmax = 4.5

event_id = dict(T1=2, T2=3)

DATA_PATH = 'data/physionet.org/files/eegmmidb/1.0.0/'

SUBJECT = 1


def get_file_names(subject, task_number):
    subject = f"S{subject:03d}"
    print(f"Loading data for subject {subject}")

    task_numbers = {
        1: TASK_1,
        2: TASK_2,
        3: TASK_3,
        4: TASK_4
    }
    task = task_numbers[task_number]
    
    file_names = [f"{subject}/{subject}R{task_number:02d}.edf" for task_number in task]
    print(f"File names: {file_names}")
    return file_names

def create_pipeline():
    csp = CSP(n_components=6, reg=None, log=True, norm_trace=False)
    lr = LogisticRegression(random_state=42)
    pipeline = make_pipeline(csp, lr)
    return pipeline

def main(task_number, subject):
    print(f"Training task {task_number} for subject {subject}")

    epochs_data = []
    for file_name in get_file_names(subject, task_number):
        # Load the data
        raw = mne.io.read_raw_edf(DATA_PATH + file_name, preload=True)
        print(f"Raw info: {raw.info}")
        raw.filter(7., 30., fir_design='firwin', skip_by_annotation='edge')
        
        events, all_event_id = mne.events_from_annotations(raw)
        picks = mne.pick_types(raw.info, eeg=True, eog=False, stim=False, exclude='bads')
        epochs = mne.Epochs(raw, events, event_id, tmin, tmax, proj=True, picks=picks, baseline=None, preload=True)
        
        #store the data in the list
        epochs_data.append(epochs)
        
    #concatenate all the data in the list
    epochs = mne.concatenate_epochs(epochs_data)
    print(epochs)
    
    pipe = create_pipeline()
    scores = cross_val_score(pipe, epochs.get_data(), epochs.events[:, -1], cv=5, n_jobs=1) # n_jobs=1 to avoid memory errors
    
    #save the model
    pipe.fit(epochs.get_data(), epochs.events[:, -1])
    model_name = f"model.joblib"
    dump(pipe, model_name)
    
    print(f"Cross validation scores: {scores.mean():.2f} +/- {scores.std():.2f}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Training script')
    parser.add_argument('task_number', type=int, choices=range(1, 5), help='Task number between 1 and 4')
    parser.add_argument('subject', type=int, choices=range(1, 110), help='Subject number between 1 and 109')
    args = parser.parse_args()

    main(args.task_number, args.subject)

