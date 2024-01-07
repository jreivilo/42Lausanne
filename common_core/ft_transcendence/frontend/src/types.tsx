
export type Users = {
	id:			number;
	login:		string;
	username:	string;
	status:		string;
	avatar:		string;
	twofactor:	boolean;
	hash2FA:	string;
}

export type Aliases = {
	id: number;
	userId:	number;
	alias:	string;
}

export type Games = {
	id:			number;
	user1Id:	number;
	user2Id:	number;
	user1:		Users;
	user2:		Users;
	user1Score:	number;
	user2Score:	number;
}

export type Tournaments = {
	id:			number;
	status:		string;
	players:	Users[];
	aliases:	Aliases[];
	games:		Games[];
}

export type PlayerScore = {
	alias:			string;
	games_played:	number;
	games_won:		number;
	games_lost:		number;
	points:			number;
}

export type Alias = {
	id: number;
	userId: number;
	alias: string;
}

export type PendingGame = {
	alias1:	Alias;
	alias2:	Alias;
}
