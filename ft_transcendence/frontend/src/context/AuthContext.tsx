import React, { createContext, useState, useEffect } from 'react';
import { useCookies } from 'react-cookie';

interface AuthContextProviderProps {
    children: React.ReactNode;
}

export const AuthContext = createContext<{
    isAuthenticated: boolean;
    token: string | null;
    login: () => void;
    logout: () => void;
}>({
    isAuthenticated: false,
    token: null,
    login: () => {},
    logout: () => {},
});

const AuthContextProvider: React.FC<AuthContextProviderProps> = ({ children }) => {
    const [cookies, setCookie, removeCookie] = useCookies(['token']);

    const token = cookies.token || null;
    const isAuthenticated = !!token;

    const login = () => {
        // Remplacez 'votre_token_oauth2' par le vrai token obtenu après l'authentification
        setCookie('token', 'votre_token_oauth2', { path: '/' });
    };

    const logout = () => {
        removeCookie('token');
    };

    useEffect(() => {
        if (token) {
            setCookie('token', token, { path: '/' });
        }
    }, [token]);

    return (
        <AuthContext.Provider value={{ isAuthenticated, token, login, logout }}>
            {children}
        </AuthContext.Provider>
    );
};

export default AuthContextProvider;
