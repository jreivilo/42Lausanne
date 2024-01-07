
import React, { useState, FunctionComponent, ChangeEvent, FormEvent, useContext, useEffect } from 'react';
import { ErrorPassword, NameMaxLenghtChat, NameMinLenghtMessage, SuccefulCreatedChat } from './Toast/ToastChat';
import CheckPassword from './CheckChatPassword';
import { createChatRoom, Chatroom } from './HandleChatComponent';
import axios from 'axios';
import { useParams } from "react-router-dom";
import { useNavigate } from 'react-router-dom';
import ChatRoom from '../pages/ChatRoom';

interface ModalProps {
  isOpen: boolean;
  setOpenModal: (open: boolean) => void;
  newChatTitle: string;

}

const Modal: FunctionComponent<ModalProps> = ({ isOpen, setOpenModal }) => {
  const [isFormVisible, setIsFormVisible] = useState(true);
  const [chatrooms, setChatrooms] = useState<Chatroom[]>([]);
  const [users, setUsers] = useState<User[]>([]);
  const history = useNavigate();
  const [messageText, setMessageText] = useState('');
  const [selectedUserId, setSelectedUserId] = useState<number | null>(null);
  const [currentUser, setCurrentUser] = useState<number>(0);

  interface User {
    id: number;
    username: string;
    status: string;
    avatar: string;
  }

  useEffect(() => {
    async function fetchUsers() {
      try {
        const response = await axios.get("/users/");
        console.log('User data:', response.data);
        setUsers(response.data);

        const meResponse = await axios.get("/users/me");
        setCurrentUser(meResponse.data.id);
      } catch (error) {
        console.error('Error fetching users', error);
      }
    }

    if (isFormVisible) {
      console.log('Fetching users...');
      // Fetch users only when the "User lists available" section is active
      fetchUsers();
    }
  }, [isFormVisible]);


  const handleUserClick = (userId: number) => {
    // Implémentez ici la logique pour envoyer un message à l'utilisateur avec l'ID userId.
    console.log(`Envoyer un message à l'utilisateur avec l'ID ${userId}`);
    setSelectedUserId(userId);
  };

  const handleMessageChange = (e: ChangeEvent<HTMLInputElement>) => {
    setMessageText(e.target.value);
  };

  const handleSendMessage = async () => {
    // Implémentez ici la logique pour envoyer le message avec le contenu de messageText.
    console.log(`Envoyer le message : ${messageText}`);
    if (messageText.trim() === '')
      NameMinLenghtMessage.showToast();
    else {
      if (selectedUserId !== null) {
        try {
          let room: any = {
            user1Id: currentUser,
            user2Id: selectedUserId,
            posts: [
              {
                text: messageText,
                authorId: currentUser,
              },
            ],
          };
          const newChatroomId = await createChatRoom(room, setChatrooms);
          if (newChatroomId != null) {
            window.location.href = `/chat/${newChatroomId}`;
            SuccefulCreatedChat.showToast();
            setIsFormVisible(false);
            setOpenModal(false);
            setMessageText('');
          }
          else {
            console.error('No user selected.');
          }
        }
        catch (error) {
          console.error('Error creating chatroom', error);
        }
      }
    };
  };

  return (
    <div className={`modalBackground ${isOpen ? 'open' : ''}`}>
      <div className="modalContainer">
        <div className="titleCloseBtn flex justify-between items-center">
          <h1>Are You Sure You Want to Continue?</h1>
          <button
            onClick={() => {
              setOpenModal(false);
            }}
            className="bg-red-500 hover:bg-red-600 text-white font-bold py-2 px-4 rounded-full shadow-md absolute top-2 right-2"
          >
            X
          </button>
        </div>
        <div className="body flex flex-col items-center">
          <>
            <h2 id="createPublic" className="w-full mt-10 mb-4 hover:bg-blue-600 text-white font-bold py-2 px-4 rounded-md shadow-md">
              User lists available
            </h2>
            <ul className="flex flex-wrap gap-4">
              {users
              .filter((user) => user.id !== currentUser)
              .map((user) => (
                <li key={user.id} className="bg-gray-200 p-2 rounded-md mb-2" onClick={() => handleUserClick(user.id)}>
                  {user.username}
                </li>
              ))}
            </ul>
            {selectedUserId !== null && (
              <div className="flex items-center mt-4">
                <input
                  type="text"
                  value={messageText}
                  onChange={handleMessageChange}
                  placeholder="Type your message..."
                  className="border border-gray-300 p-2 rounded-md mr-2 text-black"
                />
                <button
                  onClick={handleSendMessage}
                  className="bg-blue-500 hover:bg-blue-600 text-white font-bold py-2 px-4 rounded-md shadow-md"
                >
                  Send Message
                </button>
              </div>
            )}
          </>
        </div>
        <div className="footer">
          {isFormVisible ? (
            <button
              onClick={() => {
                setIsFormVisible(false);
              }}
              id="cancelBtn" className="flex items-center justify-center"
            >
              Cancel
            </button>
          ) : (
            <button
              onClick={() => {
                setOpenModal(false);
              }}
              id="cancelBtn" className="flex items-center justify-center"
            >
              Cancel
            </button>
          )}
        </div>
      </div>
    </div>
  );
}

export default Modal;
