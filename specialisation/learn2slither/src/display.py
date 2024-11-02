import tkinter as tk

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

	def run(self):
		self.window.mainloop()
