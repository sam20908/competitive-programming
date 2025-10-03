from test.lib import cli, runner, random
from random import randint
import sys
import resource

sys.setrecursionlimit(10**9)
resource.setrlimit(
    resource.RLIMIT_STACK, (resource.RLIM_INFINITY, resource.RLIM_INFINITY)
)


def main():
    args = cli.args.parse_args()
    iter = args.iterations
    for _ in range(iter):
        stdin = []

        n = randint(1, 2 * 10**5)
        q = randint(1, 2 * 10**5)
        stdin.append(f"{n} {q}")

        par = random.rand_tree_parent_list(n=n)[1:]
        stdin.append(" ".join(map(str, par)))

        for _ in range(q):
            a = randint(1, n)
            b = randint(1, n)
            stdin.append(f"{a} {b}")

        proc_ans, sol_ans = runner.run(args.program, args.solution, "\n".join(stdin))
        assert proc_ans == sol_ans


if __name__ == "__main__":
    main()
