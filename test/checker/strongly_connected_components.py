from test.lib import cli, runner
from random import randint
from collections import defaultdict


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
        proc_ans = proc_ans.split()
        sol_ans = sol_ans.split()
        assert proc_ans[0] == sol_ans[0]

        proc_kingdoms = defaultdict(list)
        for i in range(1, n + 1):
            proc_kingdoms[proc_ans[i]].append(i)
        proc_groups = sorted(proc_kingdoms.values())

        sol_kingdoms = defaultdict(list)
        for i in range(1, n + 1):
            sol_kingdoms[sol_ans[i]].append(i)
        sol_groups = sorted(sol_kingdoms.values())

        assert proc_groups == sol_groups


if __name__ == "__main__":
    main()
