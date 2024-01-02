import React, {ChangeEvent, FormEvent, useEffect, useState, useRef} from "react";
import NavBar from "../Components/Nav";
import axios, {get} from "axios";
import QRcode from "qrcode.react";

interface User {
    id: number;
    username: string;
    twofactor: boolean;
    status: string;
    avatar: string;
}

interface QRCode {
    secret: string;
    qrcode: string;
}

async function getMe() {
    try {
        const response = await axios.get('/users/me');
        return response.data as User;
    } catch (error) {
        console.error(error);
    }
}

async function getQRCode() {
    try {
        const response = await axios.get('auth/2fa/qrcode');
        console.log(response.data.otpauth);
        return response.data.otpauth;
    } catch (error) {
        console.error(error);
    }
}

const Settings: React.FC = () => {
    const [user, setUser] = useState<User | undefined>(undefined);
    const [username, setUsername] = useState<string>('');
    const [isTwoFactorEnabled, setTwoFactor] = useState<boolean>(false);
    const [qrcode, setQRCode] = useState<any>('');
    const [code, setCode] = useState<string>('');
    const [isSize, setSize] = useState<boolean>(false);

    const modalRef = useRef<HTMLDialogElement>(null);

    const openModal = async () => {
        if (modalRef.current) {
            const qr = await getQRCode();
            if (qr) {
                setQRCode(qr);
            }
            modalRef.current.showModal();
        }
    };

    const closeModal = () => {
        if (modalRef.current) {
            modalRef.current.close();
        }
    };

    const disableTwoFactorAuth = async () => {
        try {
            const response = await axios.patch(`/auth/2fa/disable`);
            setTwoFactor(false);
        } catch (error) {
            console.error(error);
        }
    }

    useEffect(() => {
        const savedSize = localStorage.getItem("size");
        if (savedSize === "oui") {
            setSize(true);
        }
    }, []);

    const toggleSize = () => {
        const newSize = !isSize;
        setSize(newSize);
        localStorage.setItem("size", newSize ? "oui" : "non");
    };

    useEffect(() => {
        async function fetchData() {
            const userData = await getMe();
            setUser(userData);
            if (userData) {
                setUsername(userData.username);
                setTwoFactor(userData.twofactor);
            }
        }

        fetchData();
    }, []);

    async function handleSubmit(event: FormEvent<HTMLFormElement>) {
        event.preventDefault();
        try {
            const response = await axios.patch(`/users/me`, {
                username,
                // avatar_url: avatarURL
                fa_enabled: isTwoFactorEnabled,
            });
            console.log(response.data);
        } catch (error) {
            console.error(error);
        }
    };
    
    async function handleCodeSubmit(event: FormEvent<HTMLFormElement>) {
        event.preventDefault();
        console.log("Code:", code);
        try {
            const response = await axios.patch(`/auth/2fa/verify`, {code: code});
            if (response.data.isValid) {
                closeModal();
                setTwoFactor(true);
            } else {
                console.log("La vérification du code a échoué");
            }
            console.log(response.data.isValid);
        } catch (error) {
            console.error(error);
        }
    };
 
    return (
        <>
            <NavBar/>
            <div className="w-full flex p-3 bg-white">
                <div className="bg-gray-200 p-4 rounded-md text-center justify-center w-full h-min">
                    <h1 className="text-3xl font-bold mb-8">Settings</h1>
                    
                    <div className="flex justify-center items-center">
                        {isSize ? (
                            <button onClick={toggleSize} className="bg-gray-900 hover:bg-pink-500 text-white py-2 px-4 rounded-md">
                                Désactiver taille police
                            </button>
                            ) : (
                            <button onClick={toggleSize} className="bg-gray-900 hover:bg-pink-500 text-white py-2 px-4 rounded-md">
                                Activer taille police
                            </button>
                        )}
                    </div>
                    <div className="flex justify-center items-center mt-2">
                        {isTwoFactorEnabled ? (
                            <button onClick={disableTwoFactorAuth} className="bg-gray-900 hover:bg-pink-500 text-white py-2 px-4 rounded-md">
                                Désactiver la 2FA
                            </button>
                        ) : (
                            <button onClick={openModal} className="bg-gray-900 hover:bg-pink-500 text-white py-2 px-4 rounded-md">
                                Activer la 2FA
                            </button>
                        )}
                    </div>
                </div>
                <dialog id="my_modal_1" className="modal" ref={modalRef}>
                    <div className="modal-box ">
                        <p className="text-center">Veuillez scanner le QR code ci-dessous avec votre application
                            d'authentification :</p>
                        <div className="flex justify-center bg-white p-4 my-8">
                            <QRcode value={qrcode}/>
                        </div>
                        <h4 className="text-l text-center"> Code de vérification :</h4>
                        <div className="flex justify-around">
                            <form onSubmit={handleCodeSubmit} className="flex justify-between">
                                <input
                                    type="text"
                                    placeholder="Code ici"
                                    className="input input-bordered input-primary w-full"
                                    value={code}
                                    onChange={(e: ChangeEvent<HTMLInputElement>) => setCode(e.target.value)}
                                />
                                <button type="submit" className="btn">Valider</button>
                            </form>
                        </div>
                        <div className="modal-action">
                            <form method="dialog">
                                <button className="btn btn-warning" onClick={closeModal}>annuler</button>
                            </form>
                        </div>
                    </div>
                </dialog>
            </div>
        </>
    )
};


export default Settings;

//TODO check avec naim pourquoi deconnection avec sa version, et changement de nom non pris en compte 
