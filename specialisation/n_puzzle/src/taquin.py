import random
import matplotlib.pyplot as plt
import numpy as np
import random
import numpy as np
import heapq # for priority queue

def generate_taquin(n):
    numbers = list(range(1, n*n))
    random.shuffle(numbers)
    empty_tile = random.randint(0, n*n-1)
    numbers.insert(empty_tile, 0)
    taquin = [numbers[i:i+n] for i in range(0, n*n, n)]
    return taquin

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

                heapq.heappush(priority_queue, (new_cost + h, new_state, new_cost, new_path))

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

    if is_solvable(taquin):
        print("The taquin is solvable")

        if is_solved(taquin):
            print("The taquin is already solved")
        else:
            result = solve(taquin, heuristic)
            if result:
                for state in result['solution_path']:
                    print()
                    print_taquin(state)
                    print()
                print("\033[92m")  # Print in green
                print(f"Total number of states opened: {result['total_states_opened']}")
                print(f"Maximum number of states in memory: {result['max_states_in_memory']}")
                print(f"Number of moves to solve: {result['solution_cost']}")
                print("Solution Path (sequence of states):")
                print("\033[0m")
            else:
                print("No solution found.")
    else:
        print("The taquin is not solvable")

if __name__ == "__main__":
    main()
