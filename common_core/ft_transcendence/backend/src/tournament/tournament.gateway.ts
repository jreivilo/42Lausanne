import {
    MessageBody,
    WebSocketGateway,
    WebSocketServer,
    SubscribeMessage,
    OnGatewayConnection,
    OnGatewayDisconnect,
	OnGatewayInit,
    ConnectedSocket,
} from '@nestjs/websockets';
import { Server } from 'ws'
import { Inject } from '@nestjs/common';
import { Socket } from 'socket.io';
import { TournamentService } from './tournament.service';
import { TStatus, Tournaments, Aliases, Games } from '@prisma/client';

export type Event<T> = {
	events: string;
	data: T;
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

function newEvent<T>(events: string, data: T): Event<T> {
	return {events: events, data: data};
}

@WebSocketGateway({
	cors: {
		origin: '*',
		credentials: true,
	},
	path: '/api/tournament',
})
export class TournamentGateway implements OnGatewayConnection, OnGatewayDisconnect {
	
	@WebSocketServer()
	server: Server;

	clients: Socket[] = [];

	constructor(@Inject(TournamentService) private readonly tournamentService: TournamentService) {
	}

    async handleConnection(@ConnectedSocket() client: Socket) {
        console.log('Tournament Client connected.');
		client.send(JSON.stringify(newEvent<{}>('registerId', {})));
		console.log("Registered clients: ", this.clients.length);
		client.send(JSON.stringify(newEvent<string>('refresh', '')));
		this.clients.forEach((c) => {
			c.send(JSON.stringify(newEvent<string>('refresh', '')));
		});
    }

    async handleDisconnect(@ConnectedSocket() client: Socket) {
        console.log('Tournament Client disconnected.');
		this.clients = this.clients.filter((c) => c !== client);
    }

	findId(client: Socket): number {
		return this.clients.findIndex((c) => c === client);
	}
	
	@SubscribeMessage('getTournament')
	async getTournament(@ConnectedSocket() client: Socket, @MessageBody() data: any)
	: Promise<Event<Tournaments>> {
		console.log("Tournament: getTournament");
		const last_tournament: Tournaments = await this.tournamentService.getLastTournament();
		return newEvent<Tournaments>('getTournament', last_tournament);
	}

	@SubscribeMessage('createTournament')
	async createTournament(@ConnectedSocket() client: Socket, @MessageBody() data: any)
	: Promise<Event<Tournaments>>  {
		console.log("Tournament: createTournament");
		const new_tournament: Tournaments = await this.tournamentService.createTournament();
		return newEvent<Tournaments>('getTournament', new_tournament);
	}

	@SubscribeMessage('getScores')
	async getScores(@ConnectedSocket() client: Socket, @MessageBody() data: any)
	: Promise<Event<PlayerScore[]>> {
		console.log("Tournament: getScores");
		const scores: PlayerScore[] = await this.tournamentService.getScores();
		return newEvent<PlayerScore[]>('getScores', scores);
	}

	@SubscribeMessage('getPendingGames')
	async getPendingGames(@ConnectedSocket() client: Socket, @MessageBody() data: any)
	: Promise<Event<PendingGame[]>>{
		console.log("Tournament: getPendingGames");
		const res = await this.tournamentService.getPendingGames();
		return newEvent<PendingGame[]>('getPendingGames', res);
	}

	@SubscribeMessage('registerId')
	async registerId(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
		console.log("Tournament: registerId id: ", data);
		this.clients[data] = client;
		return newEvent<string>('refresh', '');
	}

	@SubscribeMessage('joinTournament')
	async joinTournament(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
		var id = this.findId(client);
		console.log(`Tournament: joinTournament id: ${id} with alias ${data}`);
		const tourn = await this.tournamentService.getLastTournament();
		console.log(tourn);
		if (!tourn || tourn === undefined || tourn.status === 'done') {
			await this.tournamentService.createTournament();
		}
		if (await this.tournamentService.isInTournament(id) === true) {
			console.log(`Tournament: joinTournament id: ${id} this player is already in the Tournament`);
			return ;
		}
		console.log("Tournament: joining Tournament");
		await this.tournamentService.joinTournament(id, data);
		this.clients.forEach((c) => {
			c.send(JSON.stringify(newEvent<string>('refresh', '')));
		});
	}

	@SubscribeMessage('isInTournament')
	async isInTournament(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
		console.log(`Tournament: isInTournament`);
		var id = this.findId(client);
		const inTournament: boolean = await this.tournamentService.isInTournament(id);
		return newEvent<boolean>('isInTournament', inTournament);
	}

	@SubscribeMessage('startTournament')
	async startTournament(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
		console.log(`Tournament: startTournament`);
		await this.tournamentService.startTournament();
		this.clients.forEach((c) => {
			c.send(JSON.stringify(newEvent<string>('refresh', '')));
		});
	}

	@SubscribeMessage('stopTournament')
	async stopTournament(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
		console.log(`Tournament: stopTournament`);
		await this.tournamentService.stopTournament();
		this.clients.forEach((c) => {
			c.send(JSON.stringify(newEvent<string>('refresh', '')));
		});
	}
}
