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

        tot = 5 * 10**5
        k_max = randint(1, 5 * 10**5)
        patterns = []
        for _ in range(k_max):
            if tot == 0:
                break
            m = randint(1, tot)
            p = "".join(choices(ascii_lowercase, k=m))
            patterns.append(p)
            tot -= m

        stdin.append(str(len(patterns)))
        stdin.extend(patterns)
        print(stdin)

        proc_ans, sol_ans = runner.run(args.program, args.solution, "\n".join(stdin))
        assert proc_ans == sol_ans


if __name__ == "__main__":
    main()
