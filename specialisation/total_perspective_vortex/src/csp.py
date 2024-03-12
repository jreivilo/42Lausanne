
# coding: utf-8

import numpy as np
from sklearn.base import BaseEstimator, TransformerMixin
from scipy import linalg

# https://github.com/mne-tools/mne-python/blob/main/mne/decoding/csp.py

def compute_cov_matrices(X, y, classes):
	covs = []

	for classe in classes:
		x_classe= X[y == classe] #get data for the current class
		x_classe= np.transpose(x_classe, [1, 0, 2]) #transpose to get channels first
		x_classe= x_classe.reshape(X.shape[1], -1) #flatten the data

		covar_matrix = np.dot(x_classe, x_classe.T.conj()) / x_classe.shape[1]
		covs.append(covar_matrix)
	return np.stack(covs) #stack the covariance matrices


class CustomCSP(TransformerMixin, BaseEstimator):
	def __init__(self, n_components=4, log=True, reg=None):
		self.n_components = n_components
		self.filters_ = None
		self.mean = 0
		self.std = 0
		self.log = log
		self.reg = reg


	def fit(self, X, y):
		covs = compute_cov_matrices(X, y, np.unique(y)) #one covariance matrix per class
		eigen_values, eigen_vectors = linalg.eigh(covs[0], covs.sum(0))
		ix = np.argsort(np.abs(eigen_values - 0.5))[::-1] #sort the eigenvalues
		eigen_vectors = eigen_vectors[:, ix] #sort the eigenvectors
		self.filters_ = eigen_vectors.T #transpose the eigenvectors

		return self

	def transform(self, X):
		pick_filters = self.filters_[:self.n_components]

		# Apply spatial filters to each epoch
		X = np.asarray([np.dot(pick_filters, epoch) for epoch in X])
		X = (X ** 2).mean(axis=2) 

		if self.log:
			X = np.log(X)
		else:
			X -= X.mean(axis=0)
			X /= X.std(axis=0)
		return X

	def fit_transform(self, X, y):
		#fit and transform method for pipeline compatibility
		self.fit(X, y)
		return self.transform(X)
