import React from "react";
import { Navigate } from "react-router-dom";
import axios from 'axios';

async function getTokenValide(children: React.ReactNode) {
    const response = await axios.get('/auth/token/valid');
    const tokenStatus = response.data.res;
    console.log("token status:", tokenStatus);

    if (tokenStatus === "valid") {
        return <>{children}</>;
    } else if (tokenStatus === "need") {
        window.location.href = "/verify2fa";
    }
    else
        window.location.href = "/login";
}

const RouteProtect = ({ children }: { children: React.ReactNode }) => {
    const token = localStorage.getItem("auth_token");

    if (!token) {
        return <Navigate to="/login" replace />;
    }
    else {
        getTokenValide(children)
    }
    return <>{children}</>;
};

export default RouteProtect;
