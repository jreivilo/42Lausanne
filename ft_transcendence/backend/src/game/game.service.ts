import { Injectable } from '@nestjs/common';
import { Socket } from 'socket.io';
import { PrismaService } from 'src/prisma/prisma.service';

export interface Player {
	id: number;
	ws: WebSocket;
	paddlePosition: { x: number; y: number , length: number, hit: boolean};
	score: number;
}
  
export interface GameState {
	player1: Player;
	player2: Player;
	ballPosition: { x: number; y: number };
	ballVelocity: { x: number; y: number };
}

//speed consts
const VELOCITY_INCREASE: number = 1.1;
const MAX_VELOCITY: number = 1.1;
const constantSpeed = 1.1;

@Injectable()
export class GameService {
  private gameState: GameState;
  private client1: Socket;
  private client2: Socket;
  private mode: string;
  private tournId: number;

  constructor(private prisma: PrismaService) {
    this.initializeGameState();
	this.mode = 'none';
  }

  clearGame(client: any) {
	  this.stopGameLoop();
	  if (this.client1 && client !== this.client1) {
	this.client1.send(JSON.stringify({ type: 'redirect', data: '' }));
	  }
	  if (this.client2 && client !== this.client2) {
	this.client2.send(JSON.stringify({ type: 'redirect', data: '' }));
	  }
	  //this.initializeGameState();
  }

  logState() {
	  console.log("player1:", this.gameState.player1);
	  console.log("player2:", this.gameState.player2);
	  console.log("ball:", this.gameState.ballPosition, this.gameState.ballVelocity);
  }

  registerGame(mode: string) {
	  this.mode = mode;
  }

  // Initialize the game state
  initializeGameState() {
	  this.client1 = null;
	  this.client2 = null;
	  this.tournId = 0;
    this.gameState = {
      player1: {
        id: 0,
        ws: null,
        paddlePosition: { x: 5, y: 50, length: 14, hit: false },
        score: 0,
      },
      player2: {
        id: 0,
        ws: null,
        paddlePosition: { x: 95, y: 50, length: 14, hit: false },
        score: 0,
      },
      ballPosition: {
        x: 50,
        y: 50,
      },
      ballVelocity: {"x":0.28791511419390803,"y":-0.08429049186420078},
	  
    };
	this.resetBall();
  }

  setTournamentId(id: number) {
	  console.log("Tournament id set to: ", id);
	  this.tournId = id;
  }

  // Public method to reset the ball and paddle positions
  public resetBall() {
    this.gameState.ballPosition = { x: 50, y: 50 };
    this.gameState.player1.paddlePosition.hit = false;
    this.gameState.player2.paddlePosition.hit = false;

    // Define the angular boundaries in radians
    const minAngleRight = -Math.PI / 4;
    const maxAngleRight = Math.PI / 4;
    const minAngleLeft = 3 * Math.PI / 4;
    const maxAngleLeft = 5 * Math.PI / 4;

    // Randomly choose between left or right direction
    const isRightDirection = Math.random() > 0.5;

    let randomAngle;
    if (isRightDirection) {
        randomAngle = minAngleRight + Math.random() * (maxAngleRight - minAngleRight);
    } else {
        randomAngle = minAngleLeft + Math.random() * (maxAngleLeft - minAngleLeft);
    }
    
    const velocityX = constantSpeed * Math.cos(randomAngle);
    const velocityY = constantSpeed * Math.sin(randomAngle);

    this.gameState.ballVelocity = { x: velocityX, y: velocityY };
}


  getGameState(): GameState {
    return this.gameState;
  }

  joinGame(id : number, client: Socket): void {
		if (this.gameState.player1.id === 0 || this.gameState.player1.id === id) {
			this.initializeGameState();
			this.client1 = client;
			this.gameState.player1.id = id;
			console.log('Player 1 joined');
			return;
		} 
		else if (this.gameState.player1.id !== 0 && this.gameState.player2.id === 0) {
			this.gameState.player2.id = id;
			console.log('Player 2 joined');
			this.client2 = client;
			//send gameState to both players
			this.sendGameState();
			// Start the game after 5 seconds
			setTimeout(() => {
				this.gameLoop();
			}, 5000);
			return;
		}
		else {
			console.log('Game is full');
		}
	}


  updateGameState(newGameState: GameState): void {
    this.gameState = newGameState;
  }

  updatePlayerPosition(playerId: number, direction: string): void {
	const player = this.gameState.player1.id === playerId ? this.gameState.player1 : this.gameState.player2;
	if (direction === 'up') {
	  player.paddlePosition.y -= 0.5;
	  if (player.paddlePosition.y < 7) {
		player.paddlePosition.y = 7;
	  }
	} else if (direction === 'down') {
	  player.paddlePosition.y += 0.5;
	  if (player.paddlePosition.y > 93) {
		player.paddlePosition.y = 93;
	  }
	}
  }

  updateScore(playerId: number): void {
	const player = this.gameState.player1.id === playerId ? this.gameState.player1 : this.gameState.player2
	player.score++;
  }

  updateBallPosition(): void {
	const ball = this.gameState.ballPosition;
	const velocity = this.gameState.ballVelocity;
	ball.x += velocity.x;
	ball.y += velocity.y;
  }


  checkBallCollision(): void {
	const ball = this.gameState.ballPosition;
	const velocity = this.gameState.ballVelocity;
	const player1 = this.gameState.player1;
	const player2 = this.gameState.player2;

	// Check collision with top and bottom walls
	if (ball.y < 1.5 || ball.y > 98.5) {
	  velocity.y *= -1;
	}

	// Check collision with left wall
	if (ball.x < 0) {
	  this.updateScore(this.gameState.player2.id);
	  this.resetBall();
	}

	// Check collision with right wall
	if (ball.x > 100) {
	  this.updateScore(this.gameState.player1.id);
	  this.resetBall();
	}

	//paddle length is 10
	//check paddle collision
	//&& ball.x > 6 
	if (ball.x < 7 && player1.paddlePosition.hit == false) {
		if (ball.y > player1.paddlePosition.y - (player1.paddlePosition.length/2 + 0.9) 
			&& ball.y < player1.paddlePosition.y + (player1.paddlePosition.length/2 + 0.9)) {
		  
	  
		  // Since we're reflecting off player 1, reverse X direction
		  velocity.x *= -1;

		  //change y velocity based on where the ball hit the paddle
		  const relativeIntersectY = player1.paddlePosition.y - ball.y;
		  const normalizedRelativeIntersectionY = relativeIntersectY / (player1.paddlePosition.length/2);
		  const bounceAngle = normalizedRelativeIntersectionY * Math.PI/3;
		//   velocity.y = 0.3 * Math.sin(bounceAngle);

	  
		  player1.paddlePosition.hit = true;
		  player2.paddlePosition.hit = false;
	  
		  // Increase ball speed
		  velocity.x *= VELOCITY_INCREASE;
		  velocity.y *= VELOCITY_INCREASE;

		  //cap x velocity bettween -1 and 1
		  if (velocity.x > MAX_VELOCITY) {
			  velocity.x = MAX_VELOCITY;
		  }
		  if (velocity.x < -MAX_VELOCITY) {
			  velocity.x = -MAX_VELOCITY;
		  }
	
		}
	  }  
	  
	  //&& ball.x < 94
	  if (ball.x > 93 && player2.paddlePosition.hit == false) {
		if (ball.y > player2.paddlePosition.y - (player2.paddlePosition.length/2 + 0.9) 
			&& ball.y < player2.paddlePosition.y + (player2.paddlePosition.length/2 + 0.9)) {
		  
	  
		  // Since we're reflecting off player 2, reverse X direction
		  velocity.x *= -1;

		  //change y velocity based on where the ball hit the paddle
		  const relativeIntersectY = player2.paddlePosition.y - ball.y;
		  const normalizedRelativeIntersectionY = relativeIntersectY / (player2.paddlePosition.length/2);
		  const bounceAngle = normalizedRelativeIntersectionY * Math.PI/3;
		//   velocity.y = 0.1 * Math.sin(bounceAngle);

	  
		  player2.paddlePosition.hit = true;
		  player1.paddlePosition.hit = false;
	  
		  // Increase ball speed
		  velocity.x *= VELOCITY_INCREASE;
		  velocity.y *= VELOCITY_INCREASE;

		  //cap x velocity bettween -1 and 1
		  if (velocity.x > MAX_VELOCITY) {
			  velocity.x = MAX_VELOCITY;
		  }
		  if (velocity.x < -MAX_VELOCITY) {
			  velocity.x = -MAX_VELOCITY;
		  }
		}
	  } 
  }

	sendGameState(): void {
		const gameState = this.gameState;
		if (this.client1) {
		this.client1.send(JSON.stringify({ type: 'gameState', data: gameState }));
		}
		if (this.client2) {
		this.client2.send(JSON.stringify({ type: 'gameState', data: gameState }));
		}
	}

	stopGameLoop(): void {
		if (this.gameInterval) {
			clearInterval(this.gameInterval);
			this.gameInterval = null;
			console.log('Game loop stopped');
		}
	}

	gameInterval: NodeJS.Timeout | null = null;
	gameLoop(): void {
		// If there's already an interval running, we clear it to avoid starting multiple loops
		if (this.gameInterval) {
			clearInterval(this.gameInterval);
		}
	  
		this.gameInterval = setInterval(async () => {
			//console.log('Game loop');
			this.updateBallPosition();
			this.checkBallCollision();
			this.sendGameState();

			//if a player has 11 points, stop the game
			if (this.gameState.player1.score == 3 || this.gameState.player2.score == 3) {
				this.stopGameLoop();
				//send game over with loosers id
				console.log(this.mode);
				if (this.gameState.player1.score == 3) {
					this.client1.send(JSON.stringify({ type: 'gameOver', data: this.gameState.player1.id }));
					if (this.mode !== 'local') {
						this.client2.send(JSON.stringify({ type: 'gameOver', data: this.gameState.player1.id }));
					}
				}
				else {
					this.client1.send(JSON.stringify({ type: 'gameOver', data: this.gameState.player2.id }));
					if (this.mode !== 'local') {
						this.client2.send(JSON.stringify({ type: 'gameOver', data: this.gameState.player2.id }));
					}
				}
				if (this.mode === 'tournament') {
					const writeGame = await this.prisma.games.create({
						data: {
							user1Id: this.gameState.player1.id,
							user1Score: this.gameState.player1.score,
							user2Id: this.gameState.player2.id,
							user2Score: this.gameState.player2.score,
							tournamentsId: this.tournId,
						},
					});			
					console.log("saving tournament Game: ", writeGame);
				} else {
					console.log("Not saving Game");
				}
				this.gameState.player1.score = 0;
				this.gameState.player2.score = 0;
				//redirect user on home page after 5 seconds
				var redirectPath = '';
				if (this.mode === 'tournament') {
					redirectPath = 'tournament';
				}
				setTimeout(() => {
					this.client1.send(JSON.stringify({ type: 'redirect', data: redirectPath }));
					if (this.mode !== 'local') {
						this.client2.send(JSON.stringify({ type: 'redirect', data: redirectPath }));
					}
				}, 5000);
				
			}
		}, 35); // This runs the game loop every second, adjust this value to your needs
	}

}
