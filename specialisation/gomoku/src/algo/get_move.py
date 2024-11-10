import matplotlib
# import tkinter
# matplotlib.use('TkAgg')  # Use the TkAgg backend to prevent segmentation fault

import matplotlib.pyplot as plt
import numpy as np

from src.game.playerTokens import PlayerToken


def get_all_possible_moves(gomoku):
	"""
	Get all possible moves for the current player based on the current game state.

	:param gomoku: Gomoku game instance.
	:return: List of all possible moves.
	"""

	possible_moves = []
	for row in range(19):
		for col in range(19):
			if gomoku.board[row, col] == PlayerToken.EMPTY.value:
				possible_moves.append((row, col))

	return possible_moves

def is_move_valid(gomoku, row, col):
	
	#copy the class
	gomoku = gomoku.copy()
	
	gomoku.board[row, col] = gomoku.current_player
	if not gomoku.check_capture_and_update({"row": row, "col": col}) : #return 1 if there is a capture
		if gomoku.is_move_forbidden ({"row": row, "col": col}):
			print("Forbidden move: double three")
			return False

	return True