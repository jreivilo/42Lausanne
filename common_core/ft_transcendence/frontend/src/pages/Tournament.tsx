import React, {useState, useEffect, useRef} from 'react';
import NavBar from "../Components/Nav";
import {Tournaments, Users, Aliases, Games, PlayerScore, PendingGame} from '../types'
import axios from 'axios';
import {NotEnoughPlayers} from "../Components/Toast/ToastChat";

export const emptyTournament: Tournaments = {
    id: -1,
    status: "not_started",
    players: [],
    aliases: [],
    games: [],
};

interface IEventHandlers {
    [index: string]: any;
}

const Tournament: React.FC = () => {
    const connection = useRef<WebSocket | null>(null);
    const [tournament, setTournament] = useState<Tournaments>(emptyTournament);
    const [scores, setScores] = useState<PlayerScore[]>([]);
    const [pendingGames, setPendingGames] = useState<PendingGame[]>([]);
    const [inTournament, setInTournament] = useState<boolean>(false);
    const [alias, setAlias] = useState<string>('');
    const [me, setMe] = useState<Users>();

    useEffect(() => {
        const socket = new WebSocket(`${process.env.REACT_APP_BACKEND_SOCKET}/tournament`);

        socket.onopen = () => {
            console.log("Tournament WebSocket Opened connection");
        };

        socket.onmessage = (event) => {
            const data = JSON.parse(event.data);
            recvSocketHandler(data);
        }

        connection.current = socket;
        return () => {
            socket.close();
            console.log("Tournament WebSocket Closed connection");
        };
    }, []);

    useEffect(() => {
        console.log("tournament useState updated to: ", tournament);
    }, [tournament]);

    useEffect(() => {
        console.log("scores useState updated to: ", scores);
    }), [scores];

    useEffect(() => {
        console.log("pendingGames useState updated to: ", pendingGames);
    }), [pendingGames];

    useEffect(() => {
        console.log("inTournament useState updated to: ", inTournament);
    }), [inTournament];

    // ================== ws Handling Start ==================

    const sendSocket = (event: string, data: any) => {
        const to_transfer = {
            event: event,
            data: data,
        }
        console.log("Sending to backend: ", to_transfer);
        if (connection.current && connection.current.readyState === WebSocket.OPEN) {
            const resp = connection.current.send(JSON.stringify(to_transfer));
            return resp;
        } else {
            console.log("Tournament WebSocket error: could not send");
        }
    };

    const recvSocketHandler = (event: any) => {
        console.log("Tournament socket receive: ", event);
        const eventHandlers: IEventHandlers = {
            "registerId": registerId,
            "refresh": refresh,
            "getTournament": getTournament,
            "getScores": getScores,
            "getPendingGames": getPendingGames,
            "isInTournament": isInTournament,
        } as IEventHandlers;

        try {
            eventHandlers[event.events](event.data);
        } catch (error) {
            console.log("Tournament WebSocket: Unknown event: ", event);
        }
    }

    async function getMe() {
        const response = await axios.get('/users/me');
        setMe(response.data);
        sendSocket('registerId', response.data.id);
    }

    const registerId = (data: any) => {
        getMe();
    }
    const refresh = (data: any) => {
		sendSocket('getTournament', emptyTournament);
		sendSocket('isInTournament', '');
		sendSocket('getPendingGames', emptyTournament);
		sendSocket('getScores', emptyTournament);
    }

    const getTournament = (data: Tournaments) => {
        if (data) {
			if (data.status === 'done') {
            	sendSocket('createTournament', emptyTournament);
			} else {
            	setTournament(data);
			}
        }
    }

    const getScores = (data: PlayerScore[]) => {
        if (data.length != 0) {
            setScores(data);
        }
    }

    const getPendingGames = (data: PendingGame[]) => {
        if (data.length != 0) {
            setPendingGames(data);
        }
    }

    const isInTournament = (data: boolean) => {
        setInTournament(data);
    }

    // ================== ws Handling End ==================

    const handleJoin = () => {
        console.log("Alias: ", alias);
        sendSocket("joinTournament", alias);
    }

    const handleStartTournament = () => {

        // Check if there are enough players
        if (!scores || scores.length < 2) {
            NotEnoughPlayers.showToast();
            return;
        }
        sendSocket("startTournament", '');
    }

    const handlePlayGame = (g: PendingGame) => {
        console.log("Play game button clicked");
        console.log("Pending game: ", g);
        // TODO: A toi de jouer le boss !
		window.location.href =
			`${process.env.REACT_APP_PUBLIC_URL}/game?mode=tournament&id1=${g.alias1.userId}&id2=${g.alias2.userId}&tournid=${tournament.id}`;
    }

    const displayTitle = () => {
        return (
            <h2 className="text-center text-2xl font-bold text-black">Tournament status: <span
                className="text-pink-500"
            >{tournament.status}</span></h2>
        );
    };

    const displayPlayersScore = () => {
        // Create table with alias, games_played, games_won, games_lost, points
        return (
            <div className="flex flex-col w-full p-2">
                <h2 className="text-center text-black text-2xl font-bold">
                    Players Scores
                </h2>
                <table className="table w-full table-compact">
                    <thead>
                    <tr>
                        <th>Alias</th>
                        <th>Games Played</th>
                        <th>Games Won</th>
                        <th>Games Lost</th>
                        <th>Points</th>
                    </tr>
                    </thead>
                    <tbody>
                    {(scores.length === 0) && (
                        <tr>
                            <td className="text-center" colSpan={5}>No players are in the tournament yet</td>
                        </tr>
                    )}
                    {scores.map((score, index) => {
                        return (
                            <tr key={index}>
                                <td>{score.alias}</td>
                                <td>{score.games_played}</td>
                                <td>{score.games_won}</td>
                                <td>{score.games_lost}</td>
                                <td>{score.points}</td>
                            </tr>
                        );
                    })}
                    </tbody>
                </table>
            </div>
        )
    }

    const displayRemainingGames = () => {
        return (
            <div className="flex flex-col w-full p-2">
                <h2 className="text-center text-2xl text-black font-bold">
                    Remaining Games
                </h2>
                <table className="table w-full table-compact">
                    <thead>
                    <tr>
                        <th>Alias #1</th>
                        <th>Alias #2</th>
                        <th className="text-right">Action</th>
                    </tr>
                    </thead>
                    <tbody>
                    {pendingGames.length === 0 && (
                        <tr>
                            <td colSpan={2}>No games to be played yet.</td>
                        </tr>
                    )}
                    {pendingGames.map((pendingGame, index) => {
                        return (
                            <tr key={index}>
                                <td>{pendingGame.alias1.alias}</td>
                                <td>{pendingGame.alias2.alias}</td>
                                {
                                    index === 0 &&
                                    tournament.status === "running" &&
                                    (pendingGame.alias1.userId === me?.id || pendingGame.alias2.userId === me?.id)
                                    && (
                                    <td className="text-right">
                                        <button className="bg-gray-900 hover:bg-pink-500 text-white py-2 px-4 rounded-md"
                                                onClick={() => {
                                                    handlePlayGame(pendingGame);
                                                }}>Play Game
                                        </button>
                                    </td>
                                )}
                            </tr>
                        );
                    })}
                    </tbody>
                </table>
            </div>
        );
    };

    const joinTournament = () => { //TODO add contition to show button
        if (!inTournament && tournament.status === "not_started") {
            return (
                <div className="flex flex-row gap-2">
                    <input
                        className="bg-white border-2 text-black py-2 px-4 rounded-md"
                        type="text"
                        placeholder="Enter Alias"
                        value={alias}
                        onChange={(e: React.ChangeEvent<HTMLInputElement>) => setAlias(e.target.value)}
                    />
                    <button className="bg-gray-900 hover:bg-pink-500 text-white py-2 px-4 rounded-md"
                            onClick={handleJoin}>Join Tournament</button>
                </div>
            );
        }
    }

    const stopTournament = () => {
        if (tournament.status === "running") {
            return (
                <button className="bg-gray-900 hover:bg-pink-500 text-white py-2 px-4 rounded-md"
                        onClick={() => {
                            sendSocket("stopTournament", '');
                        }}>Stop Tournament</button>
            );
        } else {
            return;
        }
    }

    const startTournamentButton = () => {
        if (tournament.status === "not_started") {
            return (
                <button className="bg-gray-900 hover:bg-pink-500 text-white py-2 px-4 rounded-md"
                        onClick={handleStartTournament}>Start
                    Tournament</button>
            );
        } else {
            return;
        }
    }

    return (
        <>
            <NavBar/>
            <div className="flex flex-col w-fit md:w-full p-3 bg-white">
                {displayTitle()}
                <div className="flex flex-col mt-4 gap-10 w-full">
                    <div>{displayPlayersScore()}</div>
                    <div>{displayRemainingGames()}</div>
                </div>
                <div className="flex flex-col place-items-center mt-10 gap-3">
                    {joinTournament()}
                    {startTournamentButton()}
                    {stopTournament()}
                </div>
            </div>
        </>
    );
}

export default Tournament;
