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
import joblib

tmin = -0.5
tmax = 4.5
event_id = dict(T1=2, T2=3)

DATA_PATH = 'data/physionet.org/files/eegmmidb/1.0.0/'


def main(task_number, subject):
    print(f"Training task {task_number} for subject {subject}")
    subject = f"S{subject:03d}"
    print(f"Loading data for subject {subject}")
    
    file_name = f"{subject}/{subject}R{task_number:02d}.edf"
    print(f"File name: {file_name}")
    raw = mne.io.read_raw_edf(DATA_PATH + file_name, preload=True)
    raw.filter(7., 30., fir_design='firwin', skip_by_annotation='edge')
    
    events, _ = mne.events_from_annotations(raw)
    picks = mne.pick_types(raw.info, meg=False, eeg=True, stim=False, eog=False, exclude='bads')
    epochs = mne.Epochs(raw, events, event_id, tmin, tmax, proj=True, picks=picks, baseline=None, preload=True)
    print(f"Data shape: {epochs.get_data().shape}")
    print(f"Info: {epochs.info}")
    
    model = joblib.load('model.joblib')
    print(f"Model pipeline: {model}")
    
    predictions = model.predict(epochs.get_data())
    
    truth = epochs.events[:, -1]

    for i in range(len(predictions)):
        print(f"Epoch {i+1}: Prediction = {predictions[i]}, Truth = {truth[i]}")

    accuracy = accuracy_score(truth, predictions)
    print(f"Accuracy: {accuracy}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Predicting script')
    parser.add_argument('task_number', type=int, choices=range(1, 5), help='Task number between 1 and 4')
    parser.add_argument('subject', type=int, choices=range(1, 110), help='Subject number between 1 and 109')
    args = parser.parse_args()

    main(args.task_number, args.subject)