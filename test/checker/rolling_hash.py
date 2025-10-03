from test.lib import cli, runner
from random import randint, choices
from string import ascii_lowercase


def main():
    args = cli.args.parse_args()
    iter = args.iterations
    for _ in range(iter):
        stdin = []

        n = randint(1, 10**5)
        s = "".join(choices(ascii_lowercase, k=n))
        stdin.append(s)

        proc_ans, sol_ans = runner.run(args.program, args.solution, "\n".join(stdin))
        assert len(proc_ans) == len(sol_ans)
        assert proc_ans in s and sol_ans in s


if __name__ == "__main__":
    main()
