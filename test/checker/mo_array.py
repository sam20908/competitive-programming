from test.lib import cli, runner
from random import randint


def main():
    args = cli.args.parse_args()
    iter = args.iterations
    for _ in range(iter):
        stdin = []

        n = randint(1, 2 * 10**5)
        t = randint(1, 2 * 10**5)
        stdin.append(f"{n} {t}")

        a = [randint(1, 10**6) for _ in range(n)]
        stdin.append(" ".join(map(str, a)))

        for _ in range(t):
            a = randint(1, n)
            b = randint(a, n)
            stdin.append(f"{a} {b}")

        proc_ans, sol_ans = runner.run(args.program, args.solution, "\n".join(stdin))
        if proc_ans != sol_ans:
            print(proc_ans)
        assert proc_ans == sol_ans


if __name__ == "__main__":
    main()
