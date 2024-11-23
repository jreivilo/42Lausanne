import random
import tkinter as tk

from src.qlearning import QLearningAgent

class SnakeGame:
	def __init__(self, board_size=10):
		self.board_size = board_size
		self.snake = []  # List of tuples representing the snake's body
		self.green_apples = set()  # Set of green apple positions
		self.red_apple = None  # Red apple position
		self.is_game_over = False
		self.is_won = False
		self.max_duration = 0

		# Initialize snake and apples on the board
		self.initialize_snake()
		self.place_apples()
		
		self.agent = QLearningAgent()

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

	def is_valid_position(self, position):
		# Check if the position is within the board boundaries
		x, y = position
		if x < 0 or x >= self.board_size or y < 0 or y >= self.board_size:
			return False

		# Check if the position is on the snake's body
		if position in self.snake:
			return False

		return True

	def update_snake_position(self, direction):
		# Update the snake's position based on the chosen direction
		x, y = self.snake[0]
		if direction == 'up':
			new_head = (x - 1, y)
		elif direction == 'down':
			new_head = (x + 1, y)
		elif direction == 'left':
			new_head = (x, y - 1)
		elif direction == 'right':
			new_head = (x, y + 1)
		else:
			# Invalid direction
			return 'invalid_move'

		# Check for collision with walls or self
		if not self.is_valid_position(new_head):
			self.is_game_over = True
			return 'game_over'

		# Now, proceed to move the snake
		if new_head in self.green_apples:
			self.snake.insert(0, new_head)
			# Remove the eaten green apple and place a new one
			self.green_apples.remove(new_head)
			self.place_green_apple()
			# Check if the snake is long enough to win
			if len(self.snake) >= 10:
				self.is_won = True
				return 'game_won'
			return 'green_apple'
		elif new_head == self.red_apple:
			self.snake.insert(0, new_head)
			# Shorten the snake by 1
			if len(self.snake) > 2:
				self.snake.pop()
				self.snake.pop()
			else:
				# If the snake is too short, end the game
				self.is_game_over = True
				return 'game_over'
			# Place a new red apple
			self.place_red_apple()
			return 'red_apple'
		else:
			# Move the snake forward
			self.snake.insert(0, new_head)
			self.snake.pop()  # Remove the tail
			return 'empty'

	def _get_valid_moves(self):
		# Get a list of valid moves for the snake
		x, y = self.snake[0]
		possible_moves = {
			'up': (x - 1, y),
			'down': (x + 1, y),
			'left': (x, y - 1),
			'right': (x, y + 1)
		}
		valid_moves = [move for move, pos in possible_moves.items() if self.is_valid_position(pos)]
		return valid_moves

	def move_snake(self, direction=None):
		result = self.update_snake_position(direction)

		if result == 'game_over':
			# if self.agent.is_learning == False:
			print(f"Game Over! You hit a wall or yourself. Your score is {len(self.snake)} and max duration of {self.max_duration}")
			self.is_game_over = True
			if self.agent.num_training_episodes > 0 and self.agent.is_learning == True:
				# print("Is learning: ", self.agent.is_learning)
				# reset game, not the agent
				self.agent.save_q_values(filename='q_values.json')
				tmp_agent = self.agent.copy()
				self.__init__() # Reset the game
				self.agent = tmp_agent
				self.agent.num_training_episodes -= 1
				# save q values
				print(f"Training episodes left: {self.agent.num_training_episodes}")
		elif result == 'game_won':
			self.is_won = True
			# if self.agent.is_learning == False:
			print(f"Congratulations! You won the game with a score of {len(self.snake)} and max duration of {self.max_duration}")
			if self.agent.num_training_episodes > 0 and self.agent.is_learning == True:
				# print("Is learning: ", self.agent.is_learning)
				# reset game, not the agent
				self.agent.save_q_values(filename='q_values.json')
				tmp_agent = self.agent.copy()
				self.__init__()
				self.agent = tmp_agent
				self.agent.num_training_episodes -= 1
				# save q values
				print(f"Training episodes left: {self.agent.num_training_episodes}")

		self.max_duration += 1
		return result

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
