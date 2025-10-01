import subprocess


def run(program: str, solution: str, stdin: str) -> tuple[str, str]:
    """
    Executes a given program and solution with provided stdin.
    """

    input = stdin.encode()

    try:
        proc_output = subprocess.check_output(program, input=input)
    except subprocess.CalledProcessError as error:
        print("Program crashed!")
        raise error

    try:
        sol_output = subprocess.check_output(solution, input=input)
    except subprocess.CalledProcessError as error:
        print("Solution crashed!")
        raise error

    proc_ans = proc_output.decode().strip()
    proc_ans = " ".join(proc_ans.split())

    sol_ans = sol_output.decode().strip()
    sol_ans = " ".join(sol_ans.split())

    return (proc_ans, sol_ans)
