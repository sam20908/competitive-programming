from test.lib import cli, runner
from random import randint


def main():
    args = cli.args.parse_args()
    iter = args.iterations
    for _ in range(iter):
        stdin = []

        n = randint(1, 2 * 10**5)
        q = randint(1, 2 * 10**5)
        stdin.append(f"{n} {q}")

        t = [randint(1, 10**6) for _ in range(n)]
        stdin.append(" ".join(map(str, t)))

        for _ in range(q):
            type = randint(1, 2)
            a = randint(1, n)
            b = randint(a, n)
            stdin.append(f"{type} {a} {b}")

        proc_ans, sol_ans = runner.run(args.program, args.solution, "\n".join(stdin))
        assert proc_ans == sol_ans


if __name__ == "__main__":
    main()
