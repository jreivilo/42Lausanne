import {NavLink} from "react-router-dom";
import NavBar from "../Components/Nav";
import {MeContext} from "../context/MeContext";
import {useContext} from "react";
import {TypeAnimation} from 'react-type-animation';
import {useState, useEffect} from 'react';


const Home: React.FC = () => {
    const me = useContext(MeContext);
    const [isSizeEnabled, setIsSizeEnabled] = useState<boolean>(false);
    const [sizeFont, setSizeFont] = useState<string>('text-1xl');

    useEffect(() => {
        const sizeSetting = localStorage.getItem("size");
        setIsSizeEnabled(sizeSetting === "oui");
    }, []);

    const applyTextSize = (size: string) => {
        if (size === 'sm') {
            setSizeFont('text-xs');
        }
        if (size === 'base') {
            setSizeFont('text-1xl');
        }
        if (size === 'lg') {
            setSizeFont('text-3xl');
        }
    };


    return (
        <>
            <NavBar/>
            <div className="w-full flex flex-col items-center justify-start h-screen p-3 bg-white">

                <img src={require("../assets/images/pong70.png")} alt="Pong Game"
                     className="max-w-2xl rounded-xl w-full h-auto"/>
                     <div>
                        {isSizeEnabled && (
                            <div className="flex justify-center items-center  mt-5">
                                <button className="btn mx-2" onClick={() => applyTextSize('sm')}>Small</button>
                                <button className="btn mx-2" onClick={() => applyTextSize('base')}>Medium</button>
                                <button className="btn mx-2" onClick={() => applyTextSize('lg')}>Big</button>
                            </div>
                        )}
                    </div>
                <div className=" text-center mt-2 max-w-2xl px-4 py-2 bg-pink-500 text-white rounded-lg inline-block">
                    <div className={`${sizeFont} font-indie-flower`}>
                        <TypeAnimation
                            sequence={[
                                'Pong, released in 1972, is one of the earliest video games developed by Atari.' +
                                ' It \'s a simple virtual tennis game where two players compete by controlling paddles to' +
                                ' bounce a ball back and forth across the screen, scoring points with each successful exchange.' +
                                ' This classic played a significant role in popularizing video games during that era.', 1000
                            ]}
                            wrapper="span"
                            speed={55}
                            omitDeletionAnimation={true}
                            repeat={Infinity}
                        />
                    </div>
                </div>
            </div>
        </>
    );
};

export default Home;

//TODO create link vers jeux en cours et statistique de match 