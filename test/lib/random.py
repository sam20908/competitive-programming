from random import randint, sample


def rand_tree_edges(n: int) -> list[tuple[int, int]]:
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
        ed.append((leaf + 1, v + 1))
        deg[v] -= 1
        if deg[v] == 1 and v < ptr:
            leaf = v
        else:
            ptr += 1
            while deg[ptr] != 1:
                ptr += 1
            leaf = ptr
    ed.append((ptr + 1, n))
    return ed


def rand_tree_parent_list(n: int, root: int = 1) -> list[int]:
    ed = rand_tree_edges(n)
    g = [[] for _ in range(n + 1)]
    for a, b in ed:
        g[a].append(b)
        g[b].append(a)
    ans = [-1] * (n + 1)

    def dfs(u, p):
        ans[u] = p
        for v in g[u]:
            if v != p:
                dfs(v, u)

    dfs(root, -1)
    return ans[1:]


def rand_connected_graph_edges(n: int, m: int):
    assert n - 1 <= m <= n * (n - 1) // 2
    ed = rand_tree_edges(n)
    ex = set()
    deg = [0] * (n + 1)
    for a, b in ed:
        ex.add((a, b))
        ex.add((b, a))
        deg[a] += 1
        deg[b] += 1

    choices = []
    for i in range(1, n + 1):
        if deg[i] < n - 1:
            choices.append(i)

    for _ in range(m - len(ed)):
        assert len(choices) >= 2
        a, b = sample(choices, 2)
        ed.append((a, b))
        deg[a] += 1
        deg[b] += 1
        if deg[a] == n - 1:
            deg.remove(a)
        if deg[b] == n - 1:
            deg.remove(b)

    return ed
