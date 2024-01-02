import React, {useState, useEffect} from 'react';
import {MeContext} from '../context/MeContext';
import {NavLink} from 'react-router-dom';
import ModalChat from './ModalChat';
import axios from 'axios';
import {Link} from 'react-router-dom';
import {fetchChatrooms, handleDeleteChat, Chatroom} from './HandleChatComponent';
import {useCookies} from 'react-cookie';

const MyComponent: React.FC = () => {
    const [selectedMenuItem, setSelectedMenuItem] = useState('home');
    const user: any = React.useContext(MeContext);
    const [openChatModal, setOpenChatModal] = useState(false);
    const [newChatTitle, setNewChatTitle] = useState('')
    const [chatrooms, setChatrooms] = React.useState<Chatroom[]>([]);
    const [setCookie, removeCookie] = useCookies(['token_42']);
    const [userName, setUserName] = useState<string>();
    const [meId, setMe] = useState<string>('');
    const [currentId, setCurrentId] = useState<number>(0);
    const [otherId, setOtherId] = useState<number>(0);
    const [userChatName, setUserChatNmame] = useState<string>('');


    const handleLogOut = async () => {
        const confirm = window.confirm('Are you sure you want to log out?');
        if (!confirm) {
            return;
        }
        localStorage.removeItem('auth_token');
        window.location.href = '/login';
    };

    useEffect(() => {
        async function fetchData() {
            const userData = await axios.get(`/users/me`);
            setMe(userData.data.login);
            setCurrentId(userData.data.id);
        }

        fetchData();
    }, []);


    useEffect(() => { // TODO change /users/id to correct id
        fetchChatrooms().then((data) => setChatrooms(data));
    }, []);

    // Check URL to set selectedMenuItem
    useEffect(() => {
        const url = window.location.href;
        if (url.includes('/chat')) {
            setSelectedMenuItem('chat');
        } else if (url.includes('/tournament')) {
            setSelectedMenuItem('game');
        } else {
            setSelectedMenuItem('home');
        }
    }, []);

    const componentsSwitch = (key: string) => {
        switch (key) {
            case 'home':
                return (
                    <>
                        <NavLink to='/'>
                            <div className='text-center bg-gray-900 py-4 hover:bg-pink-500'>
                                Home
                            </div>
                        </NavLink>
                        <NavLink to='/profile'>
                            <div className='text-center bg-gray-900 py-4 hover:bg-pink-500'>
                                Profile
                            </div>
                        </NavLink>
                        <NavLink to='/settings'>
                            <div className='text-center bg-gray-900 py-4 hover:bg-pink-500'>
                                Setting
                            </div>
                        </NavLink>
                        <button onClick={handleLogOut}
                                className='text-center bg-gray-900 py-4 hover:bg-pink-500 w-full'>
                            Log out
                        </button>
                    </>
                );
            case 'chat':
                return (
                    <div className='flex flex-col h-full overflow-y-auto'>
                        <div className=''>
                            <button
                                onClick={() => {
                                    setOpenChatModal(true);
                                }}
                                className="text-center bg-gray-900 py-4 hover:bg-pink-500 w-full"
                            >
                                Create chat
                            </button>
                        </div>
                        {openChatModal && <ModalChat isOpen={openChatModal} setOpenModal={setOpenChatModal}
                                                     newChatTitle={newChatTitle}/>}
                        <div className="mt-4 flex flex-col space-y-4">
                            {chatrooms
                            .filter((chatrooms) => { return chatrooms.user1Id === currentId || chatrooms.user2Id === currentId; })
                            .map((value) => (
                                <div key={value.id} className="border p-2 flex flex-col">
                                    <p className="font-semibold text-white text-center"> {value.user2.login === meId ? value.user1.login : value.user2.login}</p>
                                    <div className="flex justify-between items-center mt-2">
                                        <button
                                            className="bg-pink-500 hover:bg-pink-700 text-white py-2 px-4 rounded-md"
                                            // Go to /chat/${value.id}
                                            onClick={() => {
                                                window.location.href = `/chat/${value.id}`;
                                            }}
                                        >
                                            Join
                                        </button>
                                        <button
                                            className="bg-pink-500 hover:bg-pink-700 text-white py-2 px-4 rounded-md"
                                            onClick={() => handleDeleteChat(value.id, setChatrooms)}
                                        >
                                            Delete
                                        </button>
                                    </div>
                                </div>
                            ))}
                        </div>
                    </div>
                );

            case 'game':
                return (
                    <div className='flex flex-col justify-center items-center'>
                        <Link to="/game_demo?mode=local" className='text-center bg-gray-900 py-4 hover:bg-pink-500 w-full'>
                            Local Game
                        </Link>
                        <Link to="/game?mode=normal" className='text-center bg-gray-900 py-4 hover:bg-pink-500 w-full'>
                            Play
                        </Link>
                        <Link to="/tournament" className='text-center bg-gray-900 py-4 hover:bg-pink-500 w-full'>
                            Tournament
                        </Link>
                    </div>
                );
            default:
                return null;
        }
    };

    return (
        <div className='bg-gray-900 text-white h-screen min-w-[200px]'>
            <ul className='flex flex-row justify-between items-center'>
                <button
                    className={selectedMenuItem === 'home' ? 'bg-pink-500' : 'bg-gray-900 hover:bg-pink-500 cursor-pointer'}
                    onClick={() => setSelectedMenuItem('home')}
                >
                    <img src={require('../assets/icons/home.svg').default} alt='chat icon'
                         className='w-auto h-12 px-6 py-3'/>
                </button>
                <button
                    className={selectedMenuItem === 'chat' ? 'bg-pink-500' : 'bg-gray-900 hover:bg-pink-500 cursor-pointer'}
                    onClick={() => setSelectedMenuItem('chat')}
                >
                    <img src={require('../assets/icons/chats.svg').default} alt='chat icon'
                         className='w-auto h-12 px-6 py-3'/>
                </button>
                <button
                    className={selectedMenuItem === 'game' ? 'bg-pink-500' : 'bg-gray-900 hover:bg-pink-500 cursor-pointer'}
                    onClick={() => setSelectedMenuItem('game')}
                >
                    <img src={require('../assets/icons/games.svg').default} alt='chat icon'
                         className='w-auto h-12 px-6 py-3'/>
                </button>
            </ul>
            <div>{componentsSwitch(selectedMenuItem)}</div>
        </div>
    );
};

export default MyComponent;
