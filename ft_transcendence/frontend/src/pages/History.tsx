import React, { useEffect, useState } from "react";
import { useParams } from "react-router-dom";
import axios from 'axios';
import NavBar from "../Components/Nav";

interface Match {
    id : string;
    player1 : string;
    player2: string;
    result: string;
}

const History: React.FC = () => {
    const {userId} = useParams<{userId: string }>();
    const [matches, setMatches] = useState<Match[]>([]);
    
    useEffect(() => {

        const fetchMatches = async () => {

            try {
                console.log("coucou history");
                const response = await axios.get('/users/me');
                setMatches(response.data);
            }
            catch (error) {
                console.log ("Error fetching matches: ", error);
            }
        };

        fetchMatches();
}, [userId]);

    return (
        <>
        <NavBar />
        <div className=" text-center mt-8">
            <h2 className="text-6xl font-bold mb-4 rounded-2xl bg-blue-400 text-white p-2 ml-28 shadow-2xl
            ">Match History</h2>
        {matches.length > 0 ? (
            <ul>
                {matches.map((match) => (
                    <li key={match.id} className="mb-4">
                        <div>
                            <span className="font-bold">Player 1 :</span> {match.player1}
                        </div>
                        <div>
                            <span className="font-bold">Player 2 :</span> {match.player2}
                        </div>
                        <div>
                            <span className="font-bold">Result : </span> {match.result}
                        </div>
                    </li>
                ))}
            </ul>
        ) : (
            <p className=" text-3xl font-bold ml-20" >No matches found </p>
        )}
        </div>
      </>
    );
};

export default History;