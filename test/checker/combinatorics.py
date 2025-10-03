from test.lib import cli, runner
from random import randint


def main():
    args = cli.args.parse_args()
    iter = args.iterations
    for _ in range(iter):
        stdin = []

        n = randint(1, 10**5)
        stdin.append(str(n))

        for _ in range(n):
            a = randint(1, 10**6)
            b = randint(0, a)
            stdin.append(f"{a} {b}")

        proc_ans, sol_ans = runner.run(args.program, args.solution, "\n".join(stdin))
        assert proc_ans == sol_ans


if __name__ == "__main__":
    main()
