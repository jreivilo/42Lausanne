import random
import time

from src.snake import SnakeGame
from src.display import SnakeGameGUI

# Create an instance of the Snake class
game = SnakeGame()



# Prompt the user to choose whether to use Q-learning
use_q_learning = input("Do you want to use Q-learning? (True/False): ").lower() == 'true'

print("Use Q-learning:", use_q_learning)

gui = SnakeGameGUI(game)
gui.run(use_q_learning=use_q_learning)

