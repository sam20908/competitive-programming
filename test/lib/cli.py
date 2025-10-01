import argparse

args = argparse.ArgumentParser(description="Process some arguments.")
_ = args.add_argument(
    "--program", "-p", type=str, required=True, help="Path to the program"
)
_ = args.add_argument(
    "--solution", "-s", type=str, required=True, help="Path to the solution"
)
_ = args.add_argument(
    "--iterations", "-i", type=int, default=10, help="Number of iterations"
)
