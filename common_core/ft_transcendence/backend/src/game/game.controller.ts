import { Controller, Get, Post, Body, Redirect, Render } from '@nestjs/common';
import { GameService } from './game.service';

@Controller('game')
export class GameController {
	constructor(private gameService: GameService) {}

	@Get()
	@Render('game')
	renderGame() {
		// const gameState = this.gameService.getGameState();
		// gameState.ballPosition.x = 10;
		// return { gameState };
	}
}
