import React, {useState, useEffect} from "react";
import axios from 'axios';
import ChatRoom from "../pages/ChatRoom";
import {Users} from '../types';

export interface ChatMessage {
    text: string,
    authorId: number
}

export interface Chatroom {
    id: number;
    user1Id: number;
    user2Id: number;
    user1: Users;
    user2: Users;
    posts: ChatMessage[];
    create_at: string;
    update_at: string;
    delete_at: string | null;

    //TODO: rajouter le owner
}

export const fetchChatrooms = async () => {
    try {
        const response = await axios.get('/chat');
        return response.data;
    } catch (error) {
        console.error('Error fetching chatrooms', error);
        return [];
    }
};

export const createChatRoom = async (
    room: Chatroom,
    setChatrooms: React.Dispatch<React.SetStateAction<Chatroom[]>>
): Promise<number | any> => {
    try {
        const response = await axios.post('/chat', {
            user1Id: room.user1Id,
            user2Id: room.user2Id,
            posts: room.posts,
        });
        console.log('Chat room created:', response.data);
        const newChatroomId = response.data.id;

        const updatedChatrooms = await updateChatrooms();
        setChatrooms(updatedChatrooms);

        console.log('Après mise à jour de l\'état');
        return newChatroomId;
    } catch (error) {
        console.error('Error create chatroom', error);
        return null;
    }
};

const updateChatrooms = async () => {
    try {
        const response = await axios.get('/chat');
        console.log("coucou");
        return response.data;
    } catch (error) {
        console.error('Error updating chatrooms', error);
        return [];
    }
};

export const handleDeleteChat = async (chatId: number, setChatrooms: React.Dispatch<React.SetStateAction<Chatroom[]>>) => {
    const confirm = window.confirm('Are you sure you want to delete this chat?');
    if (!confirm) {
        return;
    }
    try {
        await axios.delete(`/chat/${chatId}`);
        console.log(`Chat with ID ${chatId} has been deleted.`);
        const updatedChatrooms = await updateChatrooms();
        setChatrooms(updatedChatrooms);
        if (window.location.pathname === `/chat/${chatId}`) {
            window.location.pathname = '/';
        }
    } catch (error) {
        console.error('Error deleting chat', error);
    }
};