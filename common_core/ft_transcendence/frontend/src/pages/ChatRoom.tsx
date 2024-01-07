import React from "react";
import axios from "axios";
import ChatComponent from "../Components/ChatComponent";
import NavBar from "../Components/Nav";


interface Chat {
    id:number;
    name: string;
}

const ChatRoom: React.FC = () => {
    const [chat, setChat] = React.useState<Chat[]>([]);

    React.useEffect(() => {
        async function fetchData() {
            const response = await axios.get("/users");
            setChat(response.data);
        }

        fetchData();
    }, []);

    return (
        <>
        <NavBar />
            <h1> </h1>
        <ChatComponent />
        </>
    );

}

export default ChatRoom;