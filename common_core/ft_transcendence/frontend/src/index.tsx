import React from 'react';
import ReactDOM from 'react-dom/client';
import { BrowserRouter } from 'react-router-dom';
import './assets/scss/main.scss';
import App from './App';
import axios from 'axios';

function Main() {

  axios.defaults.baseURL = process.env.REACT_APP_BACKEND_URL || 'http://localhost:3001';
  axios.defaults.withCredentials = true;
  axios.defaults.headers.common['Authorization'] = localStorage.getItem('auth_token');
  axios.defaults.headers.post['Content-Type'] = 'application/json';

  axios.interceptors.request.use(function (config) {
    return config;
  }, function (error) {
    console.log("coucou erreur request");
    return Promise.reject(error);
  });

  axios.interceptors.response.use(function (response) {
    return response;
  }, function (error) {
    console.log("coucou erreur response");
    return Promise.reject(error);
  });

  return (
    <BrowserRouter>
      <App />
    </BrowserRouter>
  );
}

const root = ReactDOM.createRoot(document.getElementById('root') as HTMLElement);

root.render(<Main />);
