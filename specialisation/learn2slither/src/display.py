import tkinter as tk
import time
from src.utils import print_snake_vision

class SnakeGameGUI:
	def __init__(self, game):
		self.game = game
		self.cell_size = 30  # Size of each cell in the grid
		self.window = tk.Tk()
		self.window.title("Snake Game")

		# Set up canvas based on board size
		self.canvas = tk.Canvas(
			self.window,
			width=self.cell_size * game.board_size,
			height=self.cell_size * game.board_size
		)
		self.canvas.pack()

		# Draw initial board state
		self.draw_board()

	def draw_board(self):
		# for row in self.game.get_board_state():
		# 	print("".join(row))
		# print_snake_vision(self.game.get_board_state())
		self.canvas.delete("all")  # Clear previous drawings

		# Draw the grid cells
		board_state = self.game.get_board_state()
		for i in range(self.game.board_size):
			for j in range(self.game.board_size):
				x1 = j * self.cell_size
				y1 = i * self.cell_size
				x2 = x1 + self.cell_size
				y2 = y1 + self.cell_size
				
				# Define colors based on cell content
				if board_state[i][j] == 'H':  # Snake head
					color = "darkgreen"
				elif board_state[i][j] == 'S':  # Snake body
					color = "green"
				elif board_state[i][j] == 'G':  # Green apple
					color = "lightgreen"
				elif board_state[i][j] == 'R':  # Red apple
					color = "red"
				else:  # Empty cell
					color = "white"
				
				# Draw the cell
				self.canvas.create_rectangle(x1, y1, x2, y2, fill=color, outline="black")

	def run(self, train=False, num_episodes=1000, model_path='model/q_values_1000.json', want_visual=False, save_model=None, step_by_step=False):
		# Move the snake every 0.5 second
		if train == False:
			while self.game.is_game_over == False and self.game.is_won == False:
				print(f"Won: {self.game.is_won}, Game Over: {self.game.is_game_over}")
				time.sleep(0.1)
				# Load Q-values and disable learning
				self.game.agent.load_q_values(filename=model_path)
				self.game.agent.is_learning = False

				state = self.game.agent.get_state(self.game)
				action = self.game.agent.choose_action(state)
				self.game.move_snake(action)
				if want_visual:
					self.draw_board()
					self.window.update()
    
				if step_by_step:
					# Wait for enter in terminal to continue
					input("Press Enter to continue...")
  
		else :
			# Set the agent to learning mode
			self.game.agent.is_learning = True
			self.game.agent.num_training_episodes = num_episodes
			while self.game.agent.num_training_episodes > 0:
				# time.sleep(0.5)
				state = self.game.agent.get_state(self.game)
				action = self.game.agent.choose_action(state)
				reward = self.game.agent.get_reward(self.game, action)

				self.game.move_snake(action)

				next_state = self.game.agent.get_state(self.game)
				self.game.agent.update(state, action, reward)

				if want_visual:
					self.draw_board()
					self.window.update()

				# Wait for enter in terminal to continue
				if step_by_step:
					input("Press Enter to continue...")

			if save_model:
				self.game.agent.save_q_values(filename=save_model, is_final=True)
			else:
				self.game.agent.save_q_values(filename=f"q_values_{num_episodes}.json", is_final=True)
