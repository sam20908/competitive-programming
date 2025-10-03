from test.lib import cli, runner, random
from random import randint
from itertools import batched


def main():
    args = cli.args.parse_args()
    iter = args.iterations
    for _ in range(iter):
        stdin = []

        n = randint(1, 10**5)
        m = randint(n - 1, min(10**5, n * (n - 1) // 2))
        stdin.append(f"{n} {m}")

        ed = random.rand_connected_graph_edges(n, m)
        for a, b in ed:
            stdin.append(f"{a} {b}")

        proc_ans, sol_ans = runner.run(args.program, args.solution, "\n".join(stdin))

        proc_ans = proc_ans.split()
        sol_ans = sol_ans.split()
        assert proc_ans[0] == sol_ans[0]

        proc_ed = sorted([(min(a, b), max(a, b)) for a, b in batched(proc_ans[1:], 2)])
        sol_ed = sorted([(min(a, b), max(a, b)) for a, b in batched(sol_ans[1:], 2)])
        assert proc_ed == sol_ed


if __name__ == "__main__":
    main()
