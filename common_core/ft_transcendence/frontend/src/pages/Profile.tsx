import React, {useEffect, useState} from "react";
import {useParams} from "react-router-dom";
import axios from 'axios';
import NavBar from "../Components/Nav";
import {MeContext} from "../context/MeContext";

interface User {
    id: number;
    username: string;
    status: string;
    avatar: string;
}

async function getMe() {
    try {
        const response = await axios.get('/users/me');
        return response.data as User;
    } catch (error) {
        console.error(error);
    }
}

const Profile: React.FC = () => {
    const {id} = useParams<{ id: string }>();
    const [user, setUser] = useState<User | undefined>(undefined);
    const UserCtx = React.useContext(MeContext);
    const [win, setWin] = useState<number>(0);
    const [lost, setLost] = useState<number>(0);

    useEffect(() => {
        async function fetchData() {
            const userData = await getMe();
            setUser(userData);
        }

        fetchData();
    }, []);

    useEffect(() => {
        async function fetchData() {
            const userData = await getMe();
            const id = userData?.id;
            if (id) {
                const response = await axios.get(`/users/${id}/stats`);
                console.log(response.data);
                setWin(response.data.win);
                setLost(response.data.lost);
            }
        }

        fetchData();
    }, []);

    console.log(user?.id);
    console.log(user?.username);

    return (
        <>
            <NavBar/>
            <div className="w-full flex flex-col items-start p-3 bg-white">
                <div className="bg-gray-200 p-4 rounded-md flex flex-col justify-center item-center w-full">
                    <div className="flex items-center justify-center mb-4">
                        <img src={user ? user.avatar : ''} alt="avatar" className="w-10 h-10 md:w-28 md:h-28 rounded-full"/>
                        <p className="text-2xl font-bold ml-4">{user ? user.username : ''}</p>
                    </div>

                    <div className="text-xl font-semibold">Player Overview</div>
                    <progress className="progress w-full mt-3 bg-pink-500"></progress>
                    <div className="flex flex-row justify-between mx-auto">
                        <ul className="flex items-center gap-3 md:gap-12 mt-12 text-sm md:text-lg font-bold">
                            <li className="flex flex-col items-center">
                                <img className="w-10 h-10" src={require('../assets/icons/rank.svg').default} alt="Logo"/>
                                <div>rank : <span>100</span></div>
                            </li>
                            <li className="flex flex-col items-center">
                                <img className="w-10 h-10" src={require('../assets/icons/level-up.svg').default} alt="Logo"/>
                                <div>win : <span>{win}</span></div>
                            </li>
                            <li className="flex flex-col items-center">
                                <img className="w-10 h-10" src={require('../assets/icons/level-down.svg').default} alt="Logo"/>
                                <div>lost : <span>{lost}</span></div>
                            </li>
                        </ul>
                    </div>
                </div>
            </div>
        </>
    );
}

//TODO ajouter les stats recuperer du jeux.
//TDO definir un rank de depart et le faire evoluer 
export default Profile;