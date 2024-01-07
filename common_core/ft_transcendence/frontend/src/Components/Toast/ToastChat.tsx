import React from 'react';
import { toast } from 'react-toastify';
import 'react-toastify/dist/ReactToastify.css';
export const NameMaxLenghtChat = {
  showToast: () => {
    toast('Maximum length 250 characters !', {
      position: 'top-right',
      autoClose: 3000,
      hideProgressBar: false,
      closeOnClick: true,
      pauseOnHover: true,
      draggable: true,
    });
  }
}

export const NameMinLenghtMessage = {
  showToast: () => {
    toast('Please enter a valid message ', {
      position: 'top-right',
      autoClose: 3000,
      hideProgressBar: false,
      closeOnClick: true,
      pauseOnHover: true,
      draggable: true,
    });
  }
}

export const NotEnoughPlayers = {
  showToast: () => {
    toast('Not enough players to start the tournament', {
      position: 'top-right',
      autoClose: 3000,
      hideProgressBar: false,
      closeOnClick: true,
      pauseOnHover: true,
      draggable: true,
    });
  }
}

export const SuccefulCreatedChat = {
  showToast: () => {
    toast('The chatroom has been successfully created!', {
      position: 'top-right',
      autoClose: 3000,
      hideProgressBar: false,
      closeOnClick: true,
      pauseOnHover: true,
      draggable: true,
    });
  }
}

export const ErrorPassword = {
  showToast: () => {
    toast('A password must contain at least 8 characters, at least one lowercase and one uppercase letter, one special character and one number.', {
      position: 'top-right',
      autoClose: 8000,
      hideProgressBar: false,
      closeOnClick: true,
      pauseOnHover: true,
      draggable: true,
    });
  }
}