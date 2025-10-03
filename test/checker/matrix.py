from test.lib import cli, runner
from random import randint


def main():
    args = cli.args.parse_args()
    iter = args.iterations
    for _ in range(iter):
        stdin = []

        n = randint(3, 10**9)
        l = randint(1, 75)
        r = randint(l, 75)
        stdin.append(f"{n} {l} {r}")

        proc_ans, sol_ans = runner.run(args.program, args.solution, "\n".join(stdin))
        assert len(proc_ans) == len(sol_ans)


if __name__ == "__main__":
    main()
