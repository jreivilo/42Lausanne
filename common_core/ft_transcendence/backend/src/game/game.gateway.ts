import {
	SubscribeMessage,
	WebSocketGateway,
	OnGatewayConnection,
	OnGatewayDisconnect,
	WebSocketServer,
	MessageBody,
	ConnectedSocket,
  } from '@nestjs/websockets';
import { GameService } from './game.service';
import { Logger } from '@nestjs/common';
import { Server } from 'ws'
import { Socket } from 'socket.io';
import { Inject } from '@nestjs/common';
import { GameState } from './game.service';

export type Event<T> = {
	type: string;
	data: T;
}

export interface GameOptions {
	mode: string;
	id1: number;
	id2: number;
	client1: Socket | null;
	client2: Socket | null;
	started: boolean;
}

function newEvent<T>(events: string, data: T): Event<T> {
	return {type: events, data: data};
}

function sendClient(client: any, data: Event<any>) {
	client.send(JSON.stringify(data));
}

@WebSocketGateway({
	cors: {
		origin : '*',
		credentials : true,
	},
	path: '/api/game',
})
export class GameGateway implements OnGatewayConnection, OnGatewayDisconnect {

	@WebSocketServer()
	server: Server;
	currentGame: GameOptions;
  
	constructor(@Inject(GameService) private readonly gameService: GameService) {
		this.resetCurrentGame();
	}

	handleConnection(@ConnectedSocket() client: Socket) {
	  console.log('Game Gateway Client connected.');
	}
  
	handleDisconnect(@ConnectedSocket() client: Socket) {
	  console.log('Game Gateway Client disconnected.');
	  if (client === this.currentGame.client1 || client === this.currentGame.client2) {
		  console.log("RESETTING CURRENT GAME");
	  	this.resetCurrentGame();
		this.gameService.clearGame(client);
	  }
	}

	resetCurrentGame() {
		this.currentGame = {
			mode: 'none',
			id1: 0,
			id2: 0,
			client1: null,
			client2: null,
			started: false,
		};
		console.log("Game gateway: currentGame -> ", this.currentGame.mode,
					this.currentGame.id1, this.currentGame.id2, this.currentGame.started);
	}

	checkRegistration(data: GameOptions): boolean { //TODO check for normal game
		const id1 = typeof data.id1 === 'string' ? parseInt(data.id1) : data.id1;
		const id2 = typeof data.id2 === 'string' ? parseInt(data.id2) : data.id2;
		if (this.currentGame.started) {
			return false;
		}
		if (this.currentGame.mode !== 'none') {
			if (this.currentGame.mode === 'normal') {
				return (true);
			}
			if (this.currentGame.mode !== data.mode
				|| this.currentGame.id1 !== id1
			|| this.currentGame.id2 !== id2) {
				return false;
			}
		}
		return (true);
	}

	checkJoin(id: number) {
		if (this.currentGame.mode === 'tournament' || this.currentGame.mode === 'invite') {
			if (this.currentGame.id1 !== id && this.currentGame.id2 !== id) {
				return false;
			}
		}
		return (true);
	}

	@SubscribeMessage('joinGame')
	handleConnect(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
		const { id } = data;
		console.log('Game gateway: joinGame: ', id);
		this.gameService.logState();
		if (!this.checkJoin(data.id)) {
			console.log("cannot join this game!");
		}
		if (!this.currentGame.client1) {
			this.gameService.initializeGameState();
			this.currentGame.client1 = client; //TODO maybe initGame
		} else {
			this.currentGame.client2 = client;
			this.currentGame.started = true;
		}
		this.gameService.joinGame(id, client)
		console.log('Player Joined: ', this.currentGame.mode, this.currentGame.id1, this.currentGame.id2);
	}

	@SubscribeMessage('registerGame')
	registerGame(@ConnectedSocket() client: Socket, @MessageBody() data: GameOptions): Event<string> {
		console.log("Game gateway: registerGame -> ", data);
		console.log("Game gateway: currentGame -> ", this.currentGame.mode,
					this.currentGame.id1, this.currentGame.id2, this.currentGame.started);
		if (!this.checkRegistration(data)) {
			console.log("Error a game is already Registered");
			return newEvent<string>('registerGame', 'You cannot start a game');
		}
		if (data.mode === "local") {
			this.currentGame.id1 = -1;
			this.currentGame.id2 = -2;
		} else if (data.mode === "tournament" || data.mode === "invite") {
			if (data.mode === 'tournament') {
				client.send(JSON.stringify(newEvent<string>('tournamentId', '')));
			}
			this.currentGame.id1 = typeof data.id1 === 'string' ? parseInt(data.id1) : data.id1;
			this.currentGame.id2 = typeof data.id2 === 'string' ? parseInt(data.id2) : data.id2;
		} else if (data.mode === "normal") {
			this.currentGame.id1 = data.id1;
			this.currentGame.id2 = 0;
		}
		this.currentGame.mode = data.mode;
		this.gameService.registerGame(data.mode);
		console.log("Game gateway: currentGame -> ", this.currentGame.mode,
					this.currentGame.id1, this.currentGame.id2, this.currentGame.started);
		
		return (newEvent<string>('registerGame', 'ok'));
	}

	@SubscribeMessage('getGameState')
	handleGetGameState(@ConnectedSocket() client: Socket): Event<GameState> {
		console.log('Game gateway: getGameState');
		const gameState: GameState = this.gameService.getGameState();
		return (newEvent<GameState>('gameState', gameState));
	}

	@SubscribeMessage('movePaddle')
	handleMovePaddle(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
		const { playerId, direction } = data;
		this.gameService.updatePlayerPosition(playerId, direction)

		const gameState: GameState = this.gameService.getGameState();
		if (this.currentGame.client1 && this.currentGame.client2) {
			this.currentGame.client1.send(JSON.stringify(newEvent<GameState>('gameState', gameState)));
			this.currentGame.client2.send(JSON.stringify(newEvent<GameState>('gameState', gameState)));
		}
	}

	@SubscribeMessage('tournamentId')
	tournamentId(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
		console.log("tournamentId: ", data);
		this.gameService.setTournamentId(data);
	}

	@SubscribeMessage('isGameStarted')
	isGameStarted(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
		return ({events: 'isGameStarted', data: this.currentGame.started});
	}
}
