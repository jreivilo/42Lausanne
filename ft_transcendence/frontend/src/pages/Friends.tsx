
import React, { useEffect, useState } from "react";
import { useParams } from "react-router-dom";
import axios from 'axios';

interface User {
  id: number;
  username: string;
  status: string;
  avatar: string;
}

async function getUset(id: string | undefined) {
  try {
    const response = await axios.get(`/users/${id}/`);
    // console.log(response);
    return response.data as User;
  } catch (error) {
    console.error(error);
  }
}

const FriendsPage: React.FC = () => {
  const { id } = useParams<{ id: string }>();
  const [user, setUser] = useState<User | undefined>(undefined);

  useEffect(() => {
    async function fetchData() {
      const userData = await getUset(id);
      setUser(userData);
    }
    
    fetchData();
  }, [id]);
  
  return (
    <>
      <h1>User Page: {id} </h1>
      <p>User Page content goes here.</p>
      <p>{user ? JSON.stringify(user) : 'Loading...'}</p>
      <p>username: {user ? user.username : ''} </p>
      <p>status: {user ? user.status : ''} </p>
      <img src={user ? user.avatar : ''} alt="avatar" />
    </>
  );
}

export default FriendsPage;
