import random
import ast
import copy


class QLearningAgent:
    def __init__(self, epsilon=0.2, alpha=0.2, num_training_episodes=100000):
        self.epsilon = epsilon
        self.alpha = alpha
        self.q_values = {}
        # Note: This variable is not used in the code.
        self.discount_factor = 1

        self.is_learning = True
        self.num_training_episodes = num_training_episodes

    def copy(self):
        # Create a deep copy of the Q-learning agent
        new_agent = QLearningAgent(
            self.epsilon, self.alpha, self.num_training_episodes
        )
        new_agent.q_values = copy.deepcopy(self.q_values)
        return new_agent

    def get_state(self, game):
        # Get a unique representation of the game state
        # The snake knows only what is in front of him, behind him, right and
        # left
        head = game.snake[0]

        is_front_blocked = self.is_wall_or_body(game, head[0], head[1], "up")
        is_left_blocked = self.is_wall_or_body(game, head[0], head[1], "left")
        is_right_blocked = self.is_wall_or_body(
            game, head[0], head[1], "right"
        )
        is_behind_blocked = self.is_wall_or_body(
            game, head[0], head[1], "down"
        )

        is_food_up = self.is_food_on_line(game, "up")
        is_food_down = self.is_food_on_line(game, "down")
        is_food_left = self.is_food_on_line(game, "left")
        is_food_right = self.is_food_on_line(game, "right")

        state = (
            is_front_blocked,
            is_left_blocked,
            is_right_blocked,
            is_behind_blocked,
            is_food_up,
            is_food_down,
            is_food_left,
            is_food_right,
        )
        return state

    def is_wall_or_body(self, game, head_x, head_y, direction):
        # Check if there is a wall or body in the given direction
        x, y = head_x, head_y
        if direction == "up":
            x -= 1
        elif direction == "down":
            x += 1
        elif direction == "left":
            y -= 1
        elif direction == "right":
            y += 1
        return not game.is_valid_position((x, y))

    def is_food_on_line(self, game, direction):
        # Check if there is food in the given direction
        x, y = game.snake[0]
        if direction == "up":
            while x >= 0:
                if (x, y) in game.green_apples:
                    return True
                x -= 1
        elif direction == "down":
            while x < game.board_size:
                if (x, y) in game.green_apples:
                    return True
                x += 1
        elif direction == "left":
            while y >= 0:
                if (x, y) in game.green_apples:
                    return True
                y -= 1
        elif direction == "right":
            while y < game.board_size:
                if (x, y) in game.green_apples:
                    return True
                y += 1
        return False

    def get_reward(self, game, action):
        head = game.snake[0]
        x, y = head

        # Create a dictionary for distances to each visible green apple on the
        # same row or column
        apple_distances_before = {}
        for apple in game.green_apples:
            if apple[0] == x or apple[1] == y:
                distance = abs(x - apple[0]) + abs(y - apple[1])
                apple_distances_before[apple] = distance

        # Update x, y according to the action
        if action == "up":
            x -= 1
        elif action == "down":
            x += 1
        elif action == "left":
            y -= 1
        elif action == "right":
            y += 1

        reward = 0  # Initialize reward

        # Immediate rewards/penalties
        if not game.is_valid_position((x, y)):
            reward += -100
            return reward
        elif (x, y) == game.red_apple:
            reward += -10
            return reward
        elif (x, y) in game.green_apples:
            reward += 20
            return reward
        else:
            reward += -1  # Default penalty for movement

        # Recalculate distances after the move
        apple_distances_after = {}
        for apple in game.green_apples:
            if apple[0] == x or apple[1] == y:
                distance = abs(x - apple[0]) + abs(y - apple[1])
                apple_distances_after[apple] = distance

        # Adjust reward based on distance changes
        for apple in apple_distances_before:
            distance_before = apple_distances_before.get(apple, float("inf"))
            distance_after = apple_distances_after.get(apple, float("inf"))
            if distance_before is not None and distance_after is not None:
                if distance_after < distance_before:
                    reward += 2  # Moving closer to the apple
                elif distance_after > distance_before:
                    reward += -2  # Moving away from the apple

        # Reward for new apples in the same line after the move
        for apple in apple_distances_after:
            if apple not in apple_distances_before:
                reward += 2  # Now aligned with an apple

        return reward

    def get_q_value(self, state, action):
        # Return the Q-value for the state-action pair
        return self.q_values.get((state, action), 0.0)

    def choose_action(self, state):
        # Epsilon-greedy action selection
        possible_actions = ["up", "down", "left", "right"]
        if self.is_learning and random.uniform(0, 1) < self.epsilon:
            # Explore: choose a random action
            action = random.choice(possible_actions)
        else:
            # Exploit: choose the best action based on current Q-values
            q_values = [self.get_q_value(state, a) for a in possible_actions]
            max_q_value = max(q_values)
            # Handle multiple actions with the same max Q-value
            best_actions = [
                a
                for a, q in zip(possible_actions, q_values)
                if q == max_q_value
            ]
            action = random.choice(best_actions)
            if not self.is_learning:
                print(f"Best action: {action} with Q-value: {max_q_value}")
        return action

    def update(self, state, action, reward):
        if not self.is_learning:
            return
        # Update the Q-value for the state-action pair without using next_state
        current_q_value = self.get_q_value(state, action)
        # Modified Q-learning update rule without next_state
        updated_q_value = current_q_value + self.alpha * (
            reward - current_q_value
        )
        self.q_values[(state, action)] = updated_q_value

    def save_q_values(self, filename, is_final=False):
        # Save the Q-values to a file in the "model" folder
        filepath = f"model/{filename}" if is_final else f"model/tmp_{filename}"
        with open(filepath, "w") as f:
            for (state, action), value in self.q_values.items():
                f.write(f"{state},{action},{value}\n")

    def load_q_values(self, filename):
        # Load the Q-values from a file
        with open(f"model/{filename}", "r") as f:
            for line in f:
                state_str, action, value = line.strip().rsplit(",", 2)
                # Convert string to tuple safely
                state = ast.literal_eval(state_str)
                value = float(value)
                self.q_values[(state, action)] = value
