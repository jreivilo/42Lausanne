def print_snake_vision(board, board_size=10):
    # Find the snake head location
    for row in board:
        if "H" in row:
            head_row = board.index(row)
            head_col = row.index("H")
            break

    # Print Upper Wall based on head location
    print(" " + " " * (head_col) + "w" + " " * (board_size - head_col - 1))
    for index, row in enumerate(board):
        if index == head_row:
            # fill with 0 if empty
            row = ["0" if x == " " else x for x in row]
            print("w" + "".join(row) + "w")
        else:
            char = "0" if row[head_col] == " " else row[head_col]
            print(
                " " + " " * head_col + char + " " * (board_size - head_col - 1)
            )
    print(" " + " " * (head_col) + "w" + " " * (board_size - head_col - 1))
