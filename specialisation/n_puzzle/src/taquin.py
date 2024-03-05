import random
import matplotlib.pyplot as plt
import numpy as np
import random
import numpy as np
import heapq # for priority queue

def is_solvable(board):
    # Flatten the board list and count inversions.
    flat_board = [j for sub in board for j in sub if j != 0]
    inversions = 0
    for i in range(len(flat_board)):
        for j in range(i + 1, len(flat_board)):
            if flat_board[i] > flat_board[j]:
                inversions += 1
    # For a 4x4 board (or any even-sized board), the puzzle is solvable if:
    # the blank is on an even row counting from the bottom and number of inversions is odd,
    # or the blank is on an odd row from the bottom and number of inversions is even.
    blank_row_from_bottom = 4 - (flat_board.index(0) // 4)
    return (blank_row_from_bottom % 2 == 0) == (inversions % 2 == 1)

def shuffle_board(board, moves=1000):
    for _ in range(moves):
        # Find the empty space.
        empty_row, empty_col = next((r, c) for r, row in enumerate(board) for c, val in enumerate(row) if val == 0)
        # Generate a list of legal moves (up, down, left, right) that don't go off the board.
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        legal_moves = [(empty_row + dx, empty_col + dy) for dx, dy in directions if 0 <= empty_row + dx < len(board) and 0 <= empty_col + dy < len(board[0])]
        # Pick a random legal move and execute it.
        move_row, move_col = random.choice(legal_moves)
        board[empty_row][empty_col], board[move_row][move_col] = board[move_row][move_col], board[empty_row][empty_col]
    return board

def generate_taquin(size=4):
    # Initialize the board in solved state.
    board = [[n + i*size for n in range(1, size+1)] for i in range(size)]
    board[-1][-1] = 0  # Set the last tile as empty.
    shuffled_board = shuffle_board(board)
    # Ensure the shuffled board is solvable; if not, reshuffle.
    while not is_solvable(shuffled_board):
        shuffled_board = shuffle_board(board)
    return shuffled_board

def is_solvable(taquin):
    n = len(taquin)
    taquin = [tile for row in taquin for tile in row]
    inv_count = 0
    for i in range(n*n):
        for j in range(i+1, n*n):
            if taquin[i] and taquin[j] and taquin[i] > taquin[j]:
                inv_count += 1
    if n % 2 == 1:
        return inv_count % 2 == 0
    else:
        empty_row = n - taquin.index(0) // n
        return (empty_row % 2 == 1) == (inv_count % 2 == 0)

def is_solved(taquin):
    n = len(taquin)
    taquin = [tile for row in taquin for tile in row]
    return taquin == list(range(1, n*n)) + [0]

def empty_tile(taquin):
    n = len(taquin)
    for i in range(n):
        for j in range(n):
            if taquin[i][j] == 0:
                return i, j

def move_tile(taquin, direction):
    taquin_copy = [row[:] for row in taquin]
    i, j = empty_tile(taquin_copy)
    if direction == "UP":
        taquin_copy[i][j], taquin_copy[i-1][j] = taquin_copy[i-1][j], taquin_copy[i][j]
    elif direction == "DOWN":
        taquin_copy[i][j], taquin_copy[i+1][j] = taquin_copy[i+1][j], taquin_copy[i][j]
    elif direction == "LEFT":
        taquin_copy[i][j], taquin_copy[i][j-1] = taquin_copy[i][j-1], taquin_copy[i][j]
    elif direction == "RIGHT":
        taquin_copy[i][j], taquin_copy[i][j+1] = taquin_copy[i][j+1], taquin_copy[i][j]
    else:
        raise ValueError("Invalid direction")
    return taquin_copy

def get_possible_moves(taquin):
    n = len(taquin)
    i, j = empty_tile(taquin)
    moves = []
    if i > 0:
        moves.append("UP")
    if i < n-1:
        moves.append("DOWN")
    if j > 0:
        moves.append("LEFT")
    if j < n-1:
        moves.append("RIGHT")
    return moves

def manhattan_distance(state, goal):
    n = len(state)
    distance = 0
    for i in range(n):
        for j in range(n):
            if state[i][j] != goal[i][j] and state[i][j] != 0:
                x_goal, y_goal = divmod(goal[i][j] - 1, n)
                x_state, y_state = divmod(state[i][j] - 1, n)
                distance += abs(x_goal - x_state) + abs(y_goal - y_state)
    return distance

def euclidean_distance(state, goal):
    n = len(state)
    distance = 0
    for i in range(n):
        for j in range(n):
            if state[i][j] != goal[i][j] and state[i][j] != 0:
                x_goal, y_goal = divmod(goal[i][j] - 1, n)
                x_state, y_state = divmod(state[i][j] - 1, n)
                distance += np.sqrt((x_goal - x_state)**2 + (y_goal - y_state)**2)
    return distance

def hamming_distance(state, goal):
    n = len(state)
    distance = 0
    for i in range(n):
        for j in range(n):
            if state[i][j] != goal[i][j] and state[i][j] != 0:
                distance += 1
    return distance

def solve_greedy(taquin, heuristic):
    n = len(taquin)
    goal = [list(range(i * n + 1, (i + 1) * n + 1)) for i in range(n)]
    goal[-1][-1] = 0

    priority_queue = []
    heapq.heappush(priority_queue, (0, taquin, []))  # (priority, state, path)

    visited = set()
    visited.add(tuple(tuple(row) for row in taquin))

    total_states_opened = 0
    max_states_in_memory = 0

    while priority_queue:
        max_states_in_memory = max(max_states_in_memory, len(priority_queue))

        h_cost, state, path = heapq.heappop(priority_queue)
        total_states_opened += 1

        if is_solved(state):
            return {
                "total_states_opened": total_states_opened,
                "max_states_in_memory": max_states_in_memory,
                "solution_cost": len(path),
                "solution_path": path
            }

        for move in get_possible_moves(state):
            new_state = move_tile(state, move)
            new_state_tuple = tuple(tuple(row) for row in new_state)  # from list of lists to tuple of tuples
            if new_state_tuple not in visited:
                visited.add(new_state_tuple)
                new_path = path + [new_state]

                if heuristic == "manhattan":
                    h = manhattan_distance(new_state, goal)
                elif heuristic == "euclidean":
                    h = euclidean_distance(new_state, goal)
                elif heuristic == "hamming":
                    h = hamming_distance(new_state, goal)
                else:
                    raise ValueError("Invalid heuristic function")

                heapq.heappush(priority_queue, (h, new_state, new_path))

    return None

def solve_uniform_cost(taquin):
    n = len(taquin)
    goal = [list(range(i * n + 1, (i + 1) * n + 1)) for i in range(n)]
    goal[-1][-1] = 0

    priority_queue = []
    heapq.heappush(priority_queue, (0, taquin, []))  # (path cost, state, path)

    visited = set()
    visited.add(tuple(tuple(row) for row in taquin))

    total_states_opened = 0
    max_states_in_memory = 0

    while priority_queue:
        max_states_in_memory = max(max_states_in_memory, len(priority_queue))

        cost, state, path = heapq.heappop(priority_queue)
        total_states_opened += 1

        if is_solved(state):
            return {
                "total_states_opened": total_states_opened,
                "max_states_in_memory": max_states_in_memory,
                "solution_cost": cost,
                "solution_path": path
            }

        for move in get_possible_moves(state):
            new_state = move_tile(state, move)
            new_state_tuple = tuple(tuple(row) for row in new_state)
            if new_state_tuple not in visited:
                visited.add(new_state_tuple)
                new_path = path + [new_state]
                heapq.heappush(priority_queue, (cost + 1, new_state, new_path))

    return None


def solve(taquin, heuristic):
    n = len(taquin)
    goal = [list(range(i * n + 1, (i + 1) * n + 1)) for i in range(n)]
    goal[-1][-1] = 0

    priority_queue = []
    heapq.heappush(priority_queue, (0, taquin, 0, []))  # (priority, state, cost, path)

    visited = set()
    visited.add(tuple(tuple(row) for row in taquin))

    total_states_opened = 0
    max_states_in_memory = 0

    while priority_queue:
        max_states_in_memory = max(max_states_in_memory, len(priority_queue))

        _, state, cost, path = heapq.heappop(priority_queue)
        total_states_opened += 1

        if is_solved(state):
            return {
                "total_states_opened": total_states_opened,
                "max_states_in_memory": max_states_in_memory,
                "solution_cost": cost,
                "solution_path": path
            }

        for move in get_possible_moves(state):
            new_state = move_tile(state, move)
            new_state_tuple = tuple(tuple(row) for row in new_state)  # from list of lists to tuple of tuples
            if new_state_tuple not in visited:
                visited.add(new_state_tuple)
                new_path = path + [new_state]
                new_cost = cost + 1

                if heuristic == "manhattan":
                    h = manhattan_distance(new_state, goal)
                elif heuristic == "euclidean":
                    h = euclidean_distance(new_state, goal)
                elif heuristic == "hamming":
                    h = hamming_distance(new_state, goal)
                else:
                    raise ValueError("Invalid heuristic function")

                heapq.heappush(priority_queue, (new_cost + h, new_state, new_cost, new_path)) #

    return None

def print_taquin(taquin):
    for row in taquin:
        print(row)

def main():
    choice = input("Do you want to load the taquin from a file? (yes/no): ").strip().lower()

    if choice == 'yes':
        file_path = input("Enter the file path of the taquin game: ")
        try:
            with open(file_path, 'r') as file:
                lines = file.readlines()
                n = int(lines[0].strip())  # Assuming the first line contains the size
                taquin = [[int(num) for num in line.split()] for line in lines[1:n+1]]
        except Exception as e:
            print(f"An error occurred while reading the file: {e}")
            return
    else:
        try:
            n = int(input("Enter the size of the taquin game: "))
            taquin = generate_taquin(n)
        except ValueError:
            print("Invalid input")
            return

    print("Initial taquin:")
    print_taquin(taquin)

    heuristic = input("Choose the heuristic function (manhattan, euclidean, hamming), default is manhattan: ")
    if heuristic not in ["manhattan", "euclidean", "hamming"]:
        heuristic = "manhattan"
        
    model = input("Choose the model (a*, greedy or uniform cost), default is a*: ")
    if model not in ["a*", "greedy", "uniform cost"]:
        model = "a*"

    if is_solvable(taquin):
        print("The taquin is solvable")

        if is_solved(taquin):
            print("The taquin is already solved")
        else:
            print("Solving the taquin...")
            if model == "a*":
                print("Using A* algorithm")
                result = solve(taquin, heuristic)
            elif model == "greedy":
                print("Using Greedy algorithm")
                result = solve_greedy(taquin, heuristic)
            else:
                print("Using Uniform Cost algorithm")
                result = solve_uniform_cost(taquin)
            if result:
                for state in result['solution_path']:
                    print()
                    print_taquin(state)
                    print()
                print("\033[92m")  # Print in green
                print(f"Total number of states opened: {result['total_states_opened']}")
                print(f"Maximum number of states in memory: {result['max_states_in_memory']}")
                print(f"Number of moves to solve: {result['solution_cost']}")
                # print("Solution Path (sequence of states):")
                print("\033[0m")
            else:
                print("No solution found.")
    else:
        print("The taquin is not solvable")

if __name__ == "__main__":
    main()
