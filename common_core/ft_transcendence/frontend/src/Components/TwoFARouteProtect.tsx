import React from "react";
import { Navigate } from "react-router-dom";
import axios from 'axios';

async function getTokenValide(children: React.ReactNode) {
    const response = await axios.get('/auth/token/valid');
    const tokenStatus = response.data.res;
    console.log("token status:", tokenStatus);

    if (tokenStatus === "need") {
        return <>{children}</>;
    }
    else
        window.location.href = "/login";
}

const TwoFARouteProtect = ({ children }: { children: React.ReactNode }) => {
    const token = localStorage.getItem("auth_token");

    if (!token) {
        return <Navigate to="/login" replace />;
    }
    else {
        getTokenValide(children)
    }
    return <>{children}</>;
};

export default TwoFARouteProtect;
