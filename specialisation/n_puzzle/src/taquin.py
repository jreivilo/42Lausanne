import random

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

def solve(taquin):
    n = len(taquin)
    goal = [list(range(i * n + 1, (i + 1) * n + 1)) for i in range(n)]
    goal[-1][-1] = 0

    visited = set()
    visited.add(tuple(tuple(row) for row in taquin))

    queue = [(taquin, 0, [])] # (state, cost, path)
    total_states_opened = 0
    max_states_in_memory = 0

    while queue:
        state, cost, path = queue.pop(0) #pop the first element
        total_states_opened += 1
        max_states_in_memory = max(max_states_in_memory, len(queue))

        if is_solved(state):
            return {
                "total_states_opened": total_states_opened,
                "max_states_in_memory": max_states_in_memory,
                "solution_cost": cost,
                "solution_path": path
            }

        for move in get_possible_moves(state):
            new_state = move_tile(state, move)
            if tuple(tuple(row) for row in new_state) not in visited: # Check if the state has already been visited
                visited.add(tuple(tuple(row) for row in new_state))
                new_path = path + [new_state]  # Storing the move instead of the state
                # print(f"new_path: {new_path}")
                queue.append((new_state, cost + 1, new_path))

    return None

def print_taquin(taquin):
    for row in taquin:
        print(row)


n = int(input("Enter the size of the taquin game: "))
taquin = generate_taquin(n)
print("Initial taquin:")
print_taquin(taquin)

if is_solvable(taquin):
    print("The taquin is solvable")

    if is_solved(taquin):
        print("The taquin is already solved")
    else:
        result = solve(taquin)
        if result:
            print("The taquin is not solved yet, but it's solvable.")
            print(f"Total number of states opened: {result['total_states_opened']}")
            print(f"Maximum number of states in memory: {result['max_states_in_memory']}")
            print(f"Number of moves to solve: {result['solution_cost']}")
            print("Solution Path (sequence of states):")
            for state in result['solution_path']:
                print()
                print_taquin(state)
        else:
            print("No solution found.")
else:
    print("The taquin is not solvable")
