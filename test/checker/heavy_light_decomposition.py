from test.lib import cli, runner, random
from random import randint
import subprocess


def main():
    args = cli.args.parse_args()
    iter = args.iterations
    for _ in range(iter):
        stdin = []

        n = randint(1, 2 * 10**5)
        q = randint(1, 2 * 10**5)
        stdin.append(f"{n} {q}")

        v = [str(randint(1, 10**9)) for _ in range(n)]
        stdin.append(" ".join(v))

        ed = random.rand_tree_edges(n)
        for a, b in ed:
            stdin.append(f"{a} {b}")

        for _ in range(q):
            type = randint(1, 2)
            if type == 1:
                s = randint(1, n)
                x = randint(1, 10**9)
                stdin.append(f"1 {s} {x}")
            else:
                a = randint(1, n)
                b = randint(1, n)
                stdin.append(f"2 {a} {b}")

        proc_ans, sol_ans = runner.run(args.program, args.solution, "\n".join(stdin))
        assert proc_ans == sol_ans


if __name__ == "__main__":
    main()
