import random
import time

from src.snake import SnakeGame
from src.display import SnakeGameGUI
# Create an instance of the Snake class
game = SnakeGame()
gui = SnakeGameGUI(game)
gui.run()
