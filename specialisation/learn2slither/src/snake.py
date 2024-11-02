import random
import tkinter as tk

class SnakeGame:
	def __init__(self):
		self.board_size = 10  # 10x10 grid
		self.board = [[None for _ in range(self.board_size)] for _ in range(self.board_size)]
		self.snake = []  # List of tuples representing the snake's body
		self.green_apples = set()  # Set of green apple positions
		self.red_apple = None  # Red apple position
		self.is_game_over = False

		# Initialize snake and apples on the board
		self.initialize_snake()
		self.place_apples()

	def initialize_snake(self):
		# Randomly choose a starting point for the snake, ensuring it fits on the board
		x = random.randint(0, self.board_size - 3)
		y = random.randint(0, self.board_size - 1)
		self.snake = [(x, y), (x + 1, y), (x + 2, y)]  # Snake starts with 3 cells

	def place_apples(self):
		# Place two green apples randomly
		while len(self.green_apples) < 2:
			position = (random.randint(0, self.board_size - 1), random.randint(0, self.board_size - 1))
			if position not in self.snake and position not in self.green_apples:
				self.green_apples.add(position)
		
		# Place one red apple randomly
		while not self.red_apple or self.red_apple in self.snake or self.red_apple in self.green_apples:
			self.red_apple = (random.randint(0, self.board_size - 1), random.randint(0, self.board_size - 1))

	def place_green_apple(self):
		# Place a new green apple at a random position
		position = (random.randint(0, self.board_size - 1), random.randint(0, self.board_size - 1))
		while position in self.snake or position in self.green_apples or position == self.red_apple:
			position = (random.randint(0, self.board_size - 1), random.randint(0, self.board_size - 1))
		self.green_apples.add(position)

	def place_red_apple(self):
		# Place a new red apple at a random position
		position = (random.randint(0, self.board_size - 1), random.randint(0, self.board_size - 1))
		while position in self.snake or position in self.green_apples:
			position = (random.randint(0, self.board_size - 1), random.randint(0, self.board_size - 1))
		self.red_apple = position

	def get_board_state(self):
		# Provide a representation of the board with snake and apples
		board = [[' ' for _ in range(self.board_size)] for _ in range(self.board_size)]
		
		# Mark the snake's head
		if self.snake:
			head_x, head_y = self.snake[0]
			board[head_x][head_y] = 'H'  # Snake head
		
		# Mark the rest of the snake body
		for x, y in self.snake[1:]:  # Exclude the head
			board[x][y] = 'S'  # Snake body
		
		# Mark green apples
		for x, y in self.green_apples:
			board[x][y] = 'G'  # Green apple
		
		# Mark the red apple
		if self.red_apple:
			x, y = self.red_apple
			board[x][y] = 'R'  # Red apple
		
		return board