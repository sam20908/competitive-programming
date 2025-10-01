from random import randint


def rand_tree_edges(n: int) -> list[list[int]]:
    """
    Generates a random tree in linear time using random Prufer Code.

    The tree is truly random, meaning it has on average `sqrt(N)` height, thus it is very
    unlikely to get "edge case" trees such as a single chain.
    """
    code = [randint(0, n - 1) for _ in range(n - 2)]
    deg = [1] * n
    for i in code:
        deg[i] += 1
    ptr = 0
    while deg[ptr] != 1:
        ptr += 1
    leaf = ptr
    ed = []
    for v in code:
        ed.append([leaf + 1, v + 1])
        deg[v] -= 1
        if deg[v] == 1 and v < ptr:
            leaf = v
        else:
            ptr += 1
            while deg[ptr] != 1:
                ptr += 1
            leaf = ptr
    ed.append([ptr + 1, n])
    return ed
