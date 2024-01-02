import React, {useEffect} from "react";
import axios from "axios";

const Callback: React.FC = () => {

    useEffect(() => {
        const trueCode = new URLSearchParams(window.location.search).get("code");

        if (trueCode) {
            axios
                .get(`/auth/callback?code=${trueCode}`)
                .then((response) => {
                    localStorage.setItem("auth_token", response.data.token);
                    window.location.href = "/";
                })
                .catch((error) => {
                    console.error("Erreur lors de la récupération des données.", error);
                    window.location.href = "/login";
                });
        } else {
            console.error("Le code d'authentification n'a pas été reçu.");
            window.location.href = "/login";
        }
    } , []);

    return <div></div>;
}

export default Callback;
