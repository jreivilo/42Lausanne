import React, { useState, useEffect, useRef } from 'react';
import { createGlobalStyle } from 'styled-components';
import { useLocation } from 'react-router-dom';
import axios from 'axios';

const uniqueId = Math.random().toString(36).substring(2, 15) + Math.random().toString(36).substring(2, 15);

const PongGame: React.FC = () => {
	var gameState: any = null;
	const location = useLocation();
	const params = new URLSearchParams(location.search);
	const [ mode, setMode ] = useState(params.get('mode'))
	const [ id1str, setid1str ] = useState(params.get('id1'))
	const [ id2str, setid2str ] = useState(params.get('id2'))
	const [ tournIdstr, settournIdstr ] = useState(params.get('tournid'))
	const [ id1, setid1 ] = useState(0);
	const [ id2, setid2 ] = useState(0);
    const canvasRef = useRef<HTMLCanvasElement>(null); //or HTMLCanvasElement | null
	const [socket, setSocket] = useState<WebSocket | null>(null);
	const [meId, setMeId] = useState<number>(0);

	async function getMe(): Promise<number> {
		return (
			axios.get('/users/me').then((resp) => {
				console.log("id received from backend: ", resp.data.id);
				setMeId(resp.data.id);
				return (resp.data.id);
			})
		);
    }

    useEffect(() => {
		getMe().then((val) => {
			console.log("id... :", val);
			setMeId(val);
		if (!mode) {
			setMode('normal');
		}
		if (id1str && id2str) {
			console.log("register: params");
			setid1(parseInt(id1str));
			setid2(parseInt(id2str));
		}
		const newSocket = new WebSocket(`${process.env.REACT_APP_BACKEND_SOCKET}/game`);
		setSocket(newSocket);

        if (canvasRef.current) {
            const canvas = canvasRef.current; // Get the canvas element from the ref
            canvas.width = window.innerWidth; // Set the canvas width and height to fill the screen
            canvas.height = window.innerHeight; // (you can change this to any other size)
        }
		
        newSocket.onopen = () => {
            console.log('Game Connected to the server');
			if (mode === 'normal') {
            newSocket.send(JSON.stringify({ event: 'registerGame', data: { mode: mode, id1: val, id2: 0 } }));
			} else {
            newSocket.send(JSON.stringify({ event: 'registerGame', data: { mode: mode, id1: id1str, id2: id2str } }));
			}
        };

        newSocket.onmessage = (event) => {
            //console.log('Message from server: ', event.data);
            const message = JSON.parse(event.data);
            
			if (message.type !== 'gameState') {
				console.log("received: ", message);
			}
	        if (message.type === 'gameState') {
	            gameState = message.data;
	            if (gameState && gameState.player1.id === val && gameState.player2.id === 0) {
	                console.log('Waiting for player 2 to join');
	                draw_waiting_screen();
	            } else {
	                draw();
	            }
			} else if (message.type === 'tournamentId') {
				if (tournIdstr) {
					const tournId = parseInt(tournIdstr);
            		newSocket.send(JSON.stringify({ event: 'tournamentId', data: tournId }));
				}
			} else if (message.type === 'registerGame') {
				if (message.data === 'ok') {
					console.log("joinGame: id: ", val);
					newSocket.send(JSON.stringify({ event: 'joinGame', data: { id: val } }));
					newSocket.send(JSON.stringify({ event: 'getGameState' }));
				} else {
					alert("A game is already running");
	            	window.location.href = `${process.env.REACT_APP_PUBLIC_URL}`;
				}
			}
			else if (message.type === 'gameOver') {
	            const winner_player = message.data;
	
	            if (winner_player === val) {
	                alert('You won!');
	            } else {
	                alert('You lost!');
	            }
	        } else if (message.type === 'redirect') {
	            // Handle the redirection here
				window.location.href = `${process.env.REACT_APP_PUBLIC_URL}/${message.data}`;
	        }
            // More socket logic will be added in the next steps...
        };

		newSocket.onclose = () => {
			console.log('Game Disconnected from the server');
		};

		newSocket.onerror = (error) => {
			console.log('Game Error:', error);
		};

		return () => {
			newSocket.close();
		    console.log('Game Disconnected from the server');
		}
		});
    }, []);

	// Drawing Functions (I'm just going to set up the skeletons for now)
	const toPixelX = (percentage: number, boundaries: any) => {
		const normalized = percentage / 100;
		return boundaries.left + normalized * (boundaries.right - boundaries.left);
	};

	const toPixelY = (percentage: number, boundaries: any) => {
		const normalized = percentage / 100;
		return boundaries.top + normalized * (boundaries.bottom - boundaries.top);
	};

	const drawBall = (x: number, y: number, boundaries: any) => {
		var ballX = toPixelX(x, boundaries);
		var ballY = toPixelY(y, boundaries);
		var ballRadius = (boundaries.bottom - boundaries.top) * 0.015;

		// Ensure ball remains inside boundaries
		if (ballX - ballRadius < boundaries.left) ballX = boundaries.left + ballRadius;
		if (ballX + ballRadius > boundaries.right) ballX = boundaries.right - ballRadius;
		if (ballY - ballRadius < boundaries.top) ballY = boundaries.top + ballRadius;
		if (ballY + ballRadius > boundaries.bottom) ballY = boundaries.bottom - ballRadius;

		const canvas = canvasRef.current;
		if (canvas) {
			const ctx = canvas.getContext('2d');
			if (ctx) {
				ctx.beginPath();
				ctx.arc(ballX, ballY, ballRadius, 0, Math.PI * 2, false);
				ctx.fillStyle = 'white';
				ctx.fill();
				ctx.closePath();
			}
		}
	};

	const drawPaddle = (x: number, y: number, boundaries: any) => {
		var paddleWidth = (boundaries.right - boundaries.left) * 0.02;
		var paddleHeight = (boundaries.bottom - boundaries.top) * 0.14;
		var paddleX = toPixelX(x, boundaries) - paddleWidth / 2;
		var paddleY = toPixelY(y, boundaries) - paddleHeight / 2;

		// Ensure paddle remains inside boundaries
		if (paddleX < boundaries.left) paddleX = boundaries.left;
		if (paddleX + paddleWidth > boundaries.right) paddleX = boundaries.right - paddleWidth;
		if (paddleY < boundaries.top) paddleY = boundaries.top;
		if (paddleY + paddleHeight > boundaries.bottom) paddleY = boundaries.bottom - paddleHeight;

		const canvas = canvasRef.current;
		if (canvas) {
			const ctx = canvas.getContext('2d');
			if (ctx) {
				ctx.fillStyle = 'white';
				ctx.fillRect(paddleX, paddleY, paddleWidth, paddleHeight);
			}
		}
	};

	const drawBackground = () => {
		//window withd and height
		const windowWidth = window.innerWidth * 0.7;
		const windowHeight = window.innerHeight * 0.9;

		let rectWidth, rectHeight;

		if (windowWidth / windowHeight < 4/3) { // if the window is wider than 4:3
			rectWidth = windowWidth; // use full width
			rectHeight = (3/4) * rectWidth; // adjust height to maintain 4:3 ratio
		} else { // if the window is taller or exactly 4:3
			rectHeight = windowHeight; // use full height
			rectWidth = (4/3) * rectHeight; // adjust width to maintain 4:3 ratio
		}

		// Calculate the starting X and Y positions to center the rectangle in the window
		const rectX = (windowWidth - rectWidth) / 2;
		const rectY = (windowHeight - rectHeight) / 2;
	
		//console.log('rectX: ', rectX);
		//console.log('rectY: ', rectY);
		//console.log('rectWidth: ', rectWidth);
		//console.log('rectHeight: ', rectHeight);
		//console.log('windowWidth: ', windowWidth);
		//console.log('windowHeight: ', windowHeight);

		// Adjust for the border width
		var borderWidth = 1;
		const adjustedRectX = rectX + borderWidth;
		const adjustedRectY = rectY + borderWidth;
		const adjustedRectWidth = rectWidth - (2 * borderWidth);
		const adjustedRectHeight = rectHeight - (2 * borderWidth);

		// Set the fill style and draw the filled rectangle
		var fillColor = 'black';
		var borderColor = 'white';
		const canvas = canvasRef.current;
		if (canvas) {
			const ctx = canvas.getContext('2d');
			if (ctx) {
				ctx.fillStyle = fillColor;
				ctx.fillRect(adjustedRectX, adjustedRectY, adjustedRectWidth, adjustedRectHeight);

				// Set the border style and draw the border
				ctx.strokeStyle = borderColor;
				ctx.lineWidth = borderWidth;
				ctx.strokeRect(adjustedRectX, adjustedRectY, adjustedRectWidth, adjustedRectHeight);

				// Draw a dashed line in the middle of the field to separate the battlefield
				ctx.beginPath();
				ctx.setLineDash([10, 20]);  // 10 pixels dash followed by 5 pixels gap
				ctx.moveTo((windowWidth) / 2, adjustedRectY); // start at the top of the rectangle
				ctx.lineTo((windowWidth) / 2, adjustedRectY + adjustedRectHeight); // draw to the bottom of the rectangle
				ctx.stroke();

				// Clear the line dash setting for future drawings
				ctx.setLineDash([]);
		
				// Return the boundaries of the rectangle, taking the border into account
				return {
					top: adjustedRectY,
					bottom: adjustedRectY + adjustedRectHeight,
					left: adjustedRectX,
					right: adjustedRectX + adjustedRectWidth
				};
			}
		}
	};

	const printScore = (player1Score: number, player2Score: number, boundaries: any) => {
		if (typeof player1Score !== 'number' || typeof player2Score !== 'number') {
			console.error('Invalid scores provided:', player1Score, player2Score);
			return;
		}
		const fontSize = 50; // adjust as needed for your canvas size
		const offset = 50;   // a small distance to keep scores away from the center line
		const lineHeight = fontSize + 10; // adjust this for the height of the separating line
		const midX = (boundaries.left + boundaries.right) / 2;
		const player1ScoreString = player1Score.toString();
		const player2ScoreString = player2Score.toString();

		const canvas = canvasRef.current;
		if (canvas) {
			const ctx = canvas.getContext('2d');
			if (ctx) {
				ctx.font = fontSize + "px Arial";
				ctx.fillStyle = "white";
				ctx.textAlign = "center";  // Center the text on its X position
		
				// Display Player 1 score to the left of midpoint
				ctx.fillText(player1ScoreString, midX - offset, boundaries.top + fontSize + offset);
			
				// Display Player 2 score to the right of midpoint
				ctx.fillText(player2ScoreString, midX + offset, boundaries.top + fontSize + offset);
			}
		}
	};


	// Drawing the game state
	const draw = () => {

		if (canvasRef.current) {
			const canvas = canvasRef.current;
			const ctx = canvas.getContext('2d');

			if (ctx) {
				ctx.clearRect(0, 0, canvas.width, canvas.height);

				const boundaries = drawBackground();
				if (gameState)
				{
					drawBall(gameState.ballPosition.x, gameState.ballPosition.y, boundaries);
					drawPaddle(gameState.player1.paddlePosition.x, gameState.player1.paddlePosition.y, boundaries);
					drawPaddle(gameState.player2.paddlePosition.x, gameState.player2.paddlePosition.y, boundaries);
					printScore(gameState.player1.score, gameState.player2.score, boundaries);
				}
			}
		}
	};

	const [keysPressed, setKeysPressed] = useState({ up: false, down: false });

	// Update state to reflect key being pressed down
	const keyDownHandler = (event: KeyboardEvent) => {
	  if (event.key === 'ArrowUp') {
		setKeysPressed(prevState => ({ ...prevState, up: true }));
	  } else if (event.key === 'ArrowDown') {
		setKeysPressed(prevState => ({ ...prevState, down: true }));
	  }
	};
  
	// Update state to reflect key being released
	const keyUpHandler = (event: KeyboardEvent) => {
	  if (event.key === 'ArrowUp') {
		setKeysPressed(prevState => ({ ...prevState, up: false }));
	  } else if (event.key === 'ArrowDown') {
		setKeysPressed(prevState => ({ ...prevState, down: false }));
	  }
	};
  
	useEffect(() => {
	  // Add event listeners
	  document.addEventListener('keydown', keyDownHandler);
	  document.addEventListener('keyup', keyUpHandler);
  
	  // Cleanup event listeners on component unmount
	  return () => {
		document.removeEventListener('keydown', keyDownHandler);
		document.removeEventListener('keyup', keyUpHandler);
	  };
	}, []);
  
	useEffect(() => {
		//check socket connection
		if (!socket) {
			console.log('Game Socket is not open');
			return;
		}
		// Send message to server if up key is pressed
		if (keysPressed.up) {
			socket.send(JSON.stringify({ event: 'movePaddle', data: { playerId: meId, direction: 'up' } }));
			//console.log('up');
			//console.log('uniqueId: ', uniqueId);
		} else if (keysPressed.down) {
			// Send message to server if down key is pressed
			socket.send(JSON.stringify({ event: 'movePaddle', data: { playerId: meId, direction: 'down' } }));
			//console.log('down');
			//console.log('uniqueId: ', uniqueId);
		}
	});

	//resize canvas, if resize, draw again
	useEffect(() => {
		window.addEventListener('resize', draw);
		return () => {
			window.removeEventListener('resize', draw);
		};
	});

	//no scroll
	const GlobalStyle = createGlobalStyle`
	body {
		overflow: hidden;
	}
	`;

	const draw_waiting_screen = () => {
		const canvas = canvasRef.current;
		if (canvas) {
			const ctx = canvas.getContext('2d');
			if (ctx) {
				ctx.font = "30px Arial";
				ctx.fillStyle = "white";
				ctx.textAlign = "center";  // Center the text on its X position
				ctx.fillText("Waiting for player 2 to join", canvas.width / 2, canvas.height / 2);
			}
		}
	};
	

	return (
		<div className="bg-white">
			<GlobalStyle />
			<canvas ref={canvasRef} />
		</div>
	);

}

export default PongGame;
