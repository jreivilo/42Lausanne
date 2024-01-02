import React, { useState, useEffect, useRef } from 'react';
import Messages from '../chat/Message';
import axios from 'axios';
import { useParams } from 'react-router-dom';
import NavBar from "../Components/Nav";
import { NavLink } from 'react-router-dom';
import { info } from 'sass';
import { fetchChatrooms } from './HandleChatComponent';
import { NameMaxLenghtChat, NameMinLenghtMessage } from './Toast/ToastChat';

interface IEventHandlers {
    [index: string]: any;
}

const ChatComponent: React.FC = () => {
    const connection = useRef<WebSocket | null>(null);
    const connectionGame = useRef<WebSocket | null>(null);
    const [messages, setMessages] = useState<{
        text: string,
        authorId: number,
        receiverId: number,
        chatroomId: number
    }[]>([]);
    const [newMessage, setNewMessage] = useState<string>('');
    const [socket, setSocket] = useState<WebSocket | null>(null);
    const [inputMessage, setInputMessage] = useState<{ data: string }>({ data: ' ' });
    const [chatroomTitle, setChatroomTitle] = useState<string>('');
    const [infoUser1, setInfoUser1] = useState({ id: 0, login: "test", avatar: "test" });
    const [infoUser2, setInfoUser2] = useState({ id: 0, login: "test", avatar: "test" });
    const { chatId = "0" } = useParams<string>();
    const [meId, setMe] = useState<number>(0);
    const [otherId, setOtherId] = useState<number>(0);
    const [statusBlocked, setStatusBlocked] = useState<boolean>();
    const [chatroomDB, setChatroomDB] = useState({ user1Block: false, user2Block: false });
    const [gameStatus, setGameStatus] = useState<boolean>(false);

    useEffect(() => {
    	// websocket for game recovery
        const socketGame = new WebSocket(`${process.env.REACT_APP_BACKEND_SOCKET}/game`);

        socketGame.onopen = () => {
            console.log("connection websocket chat pour le game ouverte");
        };

        socketGame.onmessage = function (event) {
            var data = JSON.parse(event.data);
            recvSocketHandler(data);
        }

        connectionGame.current = socketGame;

        return () => {
            socketGame.close();
            console.log("closed socket 2");
        };
    }, []);

    // Websoket for Chat

    useEffect(() => {
        const socket = new WebSocket(`${process.env.REACT_APP_BACKEND_SOCKET}`);

        socket.onopen = () => {
            console.log('Connexion WebSocket ouverte.');
        };

        socket.onmessage = function (event) {
            var data = JSON.parse(event.data);
            recvSocketHandler(data);
        }

        connection.current = socket;

        return () => {
            socket.close();
            console.log("closed connection");
        };
    }, []);

    const sendSocket = (event: string, data: any) => {
        const to_transfer = {
            event: event,
            data: data,
        }
        if (connection.current && connection.current.readyState === WebSocket.OPEN) {
            const resp = connection.current.send(JSON.stringify(to_transfer));
            return resp;
        } else {
            console.log("Chat WebSocket error: could not send");
        }
    };

    const recvSocketHandler = (event: any) => {
        console.log("Chat socket receive: ", event);
        const eventHandlers: IEventHandlers = {
            "isGameStarted": isGameStartedHanlder,
            "refresh": refresh,
            "GetMessages": GetMessagesHandler,
            "AlertUserBlocked": GetAlertUserBlocked,
			"inviteGameFromChat": inviteGameFromChatHandler,
        } as IEventHandlers;

        try {
            eventHandlers[event.events](event.data);
        } catch (error) {
            console.log("Chat WebSocket: Unknown event: ", event);
        }
    }

    const sendSocketGame = (event: string, data: any) => {
        const to_transfer = {
            event: event,
            data: data,
        }
        if (connectionGame.current && connectionGame.current.readyState === WebSocket.OPEN) { //TODO
            const resp = connectionGame.current.send(JSON.stringify(to_transfer));
            return resp;
        } else {
            console.log("Chat WebSocket/game error: could not send");
        }
    };

    const recvSocketHandlerGame = (event: any) => {
        const eventHandlers: IEventHandlers = {
			//"isGameStarted": isGameStartedHanlder,
        } as IEventHandlers;

        try {
            eventHandlers[event.events](event.data);
        } catch (error) {
            console.log("Chat WebSocket/game: Unknown event: ", event);
        }
    }

    const isGameStartedHanlder = (data: any) => {
		console.log(data);
        setGameStatus(data);
    }

	const inviteGameFromChatHandler = (data: any) => {
		alert("You have been invited to play a game");
		window.location.href = `${process.env.REACT_APP_PUBLIC_URL}/game?mode=invite&id1=${data.meId}&id2=${data.otherId}`;
	}

    // end websocket game


    const fetchChatroomDetails = async () => {
        try {
            const response = await axios.get(`/chat/${chatId}`);
            const newInfoUser1 = await axios.get(`/users/${response.data.user1Id}`);
            const newInfoUser2 = await axios.get(`/users/${response.data.user2Id}`);
            console.log("Informations user 2 pour profile ", newInfoUser2.data.id);
            const Iam = await axios.get('/users/me');
            setMe(Iam.data.id);
            setChatroomDB(response.data);

            setInfoUser1(infoUser1 => ({
                ...infoUser1,
                ...newInfoUser1.data,
            }));

            setInfoUser2(infoUser2 => ({
                ...infoUser2,
                ...newInfoUser2.data,
            }));
            const other = await newInfoUser1.data.id === Iam.data.id ? newInfoUser2.data.id : newInfoUser1.data.id;
            setOtherId(other);
            setChatroomTitle(response.data.title);
        } catch (error) {
            console.error('Error fetching chatroom details', error);
        }
    };

    useEffect(() => {

        fetchChatroomDetails();
    }, [chatId]);

    // handlers start

    const refresh = async (data: any) => {
        if (meId === 0) {
            const Iam = await axios.get('/users/me');
            console.log("Iam", Iam);
            setMe(Iam.data.id);
            console.log("meId✅", Iam.data.id);
            sendSocket('registerNewClient', Iam.data.id);
        }
        sendSocket('GetMessages', parseInt(chatId));
        sendSocketGame('isGameStarted', '');
        fetchChatroomDetails();
    }

    const GetMessagesHandler = (data: any) => {
        setMessages(data);
    }

    const blockUserHandler = () => {
        sendSocket('blockUsers', { meId: meId, infoUser1: infoUser1, chatId: parseInt(chatId) });
    }

    const unBlockUserHandler = () => {
        sendSocket('unBlockUsers', { meId: meId, infoUser1: infoUser1, chatId: parseInt(chatId) });
    }

    const GetAlertUserBlocked = () => {
        setStatusBlocked(true);
    }

    const inviteGameFromChat = () => {
        console.log("inviteGameFromChat");
        console.log("meId", meId);
        console.log("otherId", otherId);
        console.log("chatId", parseInt(chatId));
        sendSocket('inviteGameFromChat', { meId: meId, otherId: otherId, chatId: parseInt(chatId) });
		window.location.href = `${process.env.REACT_APP_PUBLIC_URL}/game?mode=invite&id1=${meId}&id2=${otherId}`;
    }

    // handlers end


    const sendNewMessage = () => {
        console.log("ici dans sendMessage");
        if (newMessage.trim() === "") {
            NameMinLenghtMessage.showToast();
            return;
        }
        const foo = {
            text: newMessage,
            authorId: meId,
            receiverId: infoUser1.id === meId ? infoUser2.id : infoUser1.id,
            chatroomId: parseInt(chatId, 10),
        }
        // console.log("foo is", foo);
        if (foo.text.length > 250)
        {
            NameMaxLenghtChat.showToast();
        }
        else
        {
            sendSocket('newMessage', foo);
            setMessages([...messages, foo]);
            setNewMessage('');
        }
    }

    const handleKeyPress = (e: React.KeyboardEvent<HTMLInputElement>) => {
        if (e.key === 'Enter') {
            sendNewMessage();
        }
    }

    const displayChatUsersBanner = () => {
        return (
            <div className='flex flex-col items-start bg-gray-200 w-full p-3'>
                <div className='flex'>
                    <img className='w-20 h-20 rounded-full' alt='User avatar'
                        src={infoUser1.id === meId ? infoUser2.avatar : infoUser1.avatar} />
                    <h4 className='grow text-2xl mt-5 ml-2'>{infoUser1.id === meId ? infoUser2.login : infoUser1.login}</h4>
                </div>
                <div className='flex flex-row justify-center items-center gap-2 ml-2 mt-4'>

                    {
                        (gameStatus === false) ?
                            <button
                                onClick={inviteGameFromChat}
                                className='bg-gray-900 hover:bg-pink-500 text-white px-2 py-1 rounded h-min'
                            >
                                Invite to play
							</button>
								:
                            <button
                                className='bg-red-600 text-white px-2 py-1 rounded h-min'
                            disabled>
                                A game is running
                            </button>
                    }
                    {
                        (otherId === infoUser2.id && !chatroomDB.user2Block) || (otherId === infoUser1.id && !chatroomDB.user1Block)
                            ?
                            <button
                                onClick={blockUserHandler}
                                className='send-button bg-blue-300 text-white px-2 py-1 rounded h-min'
                            >
                                Block
                            </button>
                            :
                            <button
                                onClick={unBlockUserHandler}
                                className='send-button bg-pink-500 text-white px-2 py-1 rounded h-min'
                            >
                                Unblock
                            </button>
                    }


                    <NavLink to={`/profile/${otherId}`}>
                        <div className='bg-gray-900 hover:bg-pink-500 text-white px-2 py-1 rounded h-min'>
                            <p>Show</p>
                        </div>
                    </NavLink>
                </div>
            </div>
        );
    }

    const sendMess = () => {
        return (
            ((meId === infoUser1.id && !chatroomDB.user1Block) || (meId === infoUser2.id && !chatroomDB.user2Block)) ? (
                <div className='flex flex-row bg-gray-200 w-full px-4 py-8'>
                    <div className='flex flex-row w-full gap-2'>
                        <input
                            type='text'
                            value={newMessage}
                            onChange={(e) => setNewMessage(e.target.value)}
                            onKeyPress={handleKeyPress}
                            className='bg-gray-100 w-full p-2 rounded'
                        />
                        <button
                            onClick={sendNewMessage}
                            className='bg-gray-900 hover:bg-pink-500 text-white py-2 px-4 rounded h-min'
                        >
                            Send
                        </button>
                    </div>
                </div>
            ) : (
                <div className='bg-gray-200 fixed bottom-0 w-full py-10 shadow-lg'>
                    you have been blocked
                </div>
            )
        );
    };

    return (
        <>
            <NavBar />
            <div className='flex flex-col w-full h-screen bg-white'>
                {displayChatUsersBanner()}
                <div className='flex flex-col w-full gap-2 p-4 h-full overflow-y-auto'>
                    {messages.map((message, index) => {
                        if (message.authorId === meId) {
                            console.log("meId", meId);
                            return (<div className='chat-bubble bg-pink-500 text-white self-end' key={index}>
                                {message.text}
                            </div>);
                        } else {
                            console.log("message from other");
                            return (<div className='chat-bubble bg-gray-900 text-white' key={index}>
                                {message.text}
                            </div>);
                        }
                    })}
                </div>
                {sendMess()}
            </div>
        </>
    );
};

export default ChatComponent;
