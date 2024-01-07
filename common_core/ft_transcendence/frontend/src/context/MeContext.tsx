import React from "react";

export interface Me {
    id: string;
    login: string;
    name: string;
    avatar_url: string;
    status: string;
    // twofactor: boolean;
    created_at: string;
    updated_at: string;
}

export const MeContext = React.createContext<Me | null>(null);