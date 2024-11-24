import argparse
import time
from src.snake import SnakeGame
from src.display import SnakeGameGUI


def main():
    # Set up argument parsing
    parser = argparse.ArgumentParser(
        description="Run the Snake game with or without Q-learning."
    )

    # Argument to specify if we want to train a new model or use a saved model
    parser.add_argument(
        "--train", action="store_true", help="Train a new Q-learning model"
    )
    parser.add_argument(
        "--use_model", type=str, help="Path to saved model for inference"
    )
    parser.add_argument(
        "--save_model", type=str, help="Path to save the trained model"
    )

    # Argument to specify if we want visual output
    parser.add_argument(
        "--visual", action="store_true", help="Display the game visually"
    )

    # arg number of episodes
    parser.add_argument(
        "--num_episodes",
        type=int,
        help="Number of episodes to train the model",
    )

    parser.add_argument(
        "--step_by_step",
        action="store_true",
        help="Step by step execution of the game",
    )

    # custom board size
    parser.add_argument(
        "--board_size", type=int, default=None, help="Size of the board"
    )

    # Parse the arguments
    args = parser.parse_args()

    # Create an instance of the Snake game
    if args.board_size:
        game = SnakeGame(board_size=args.board_size)
    else:
        game = SnakeGame()

    # if no number of episodes is specified, default to 1000
    if not args.num_episodes:
        args.num_episodes = 10

    # Decide whether to use Q-learning based on the arguments
    if args.train:
        train = True
    elif args.use_model:
        print(f"Loading saved model from {args.use_model}...")
        train = False
        model_path = args.use_model
    else:
        print("No action specified. Defaulting to training Q-learning...")
        time.sleep(1)
        train = True

    # Set up the GUI and run the game
    gui = SnakeGameGUI(game)

    if train:
        print("Training the Q-learning model...")
        time.sleep(1)
        gui.run(
            train=True,
            num_episodes=args.num_episodes,
            want_visual=args.visual,
            save_model=args.save_model,
            step_by_step=args.step_by_step,
        )
    else:
        print("Running the game using the saved model...")
        gui.run(
            train=False,
            model_path=model_path,
            want_visual=args.visual,
            step_by_step=args.step_by_step,
        )


if __name__ == "__main__":
    # THIS IS BAD PRACTICE, BUT IT IS USED TO CATCH ALL EXCEPTIONS FOR THE
    # SAKE OF THE CORRECTION
    try:
        main()
    # cath all exceptions
    except Exception as e:
        print(f"An error occurred: {e}")
        print("Exiting...")
        exit()
