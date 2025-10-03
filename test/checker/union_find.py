from test.lib import cli, runner
from random import randint


def main():
    args = cli.args.parse_args()
    iter = args.iterations
    for _ in range(iter):
        stdin = []

        n = randint(1, 10**5)
        m = randint(1, 2 * 10**5)
        stdin.append(f"{n} {m}")
        for _ in range(m):
            a = randint(1, n)
            b = randint(1, n)
            stdin.append(f"{a} {b}")

        proc_ans, sol_ans = runner.run(args.program, args.solution, "\n".join(stdin))
        assert proc_ans == sol_ans


if __name__ == "__main__":
    main()
