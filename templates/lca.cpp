struct LCA
{
    int lg = 0;
    vector<vector<int>> up;
    vector<int> in, out;
    lca(vector<vector<int>> &g, int root)
        : lg(__lg(g.size())), up(g.size(), vector<int>(lg + 1)), in(g.size()), out(g.size())
    {
        int time = 0;
        auto f = [&](auto &self, int u, int p) -> void
        {
            in[u] = ++time;
            up[u][0] = p;
            for (int p = 1; p <= lg; p++)
                up[u][p] = up[up[u][p - 1]][p - 1];
            for (int next : g[u])
                if (next != p)
                    self(self, next, u);
            out[u] = ++time;
        };
        f(f, root, root);
    }
    bool is_ancestor(int u, int v)
    {
        return in[u] <= in[v] && out[u] >= out[v]; // if u is ancestor of v
    }
    int query(int u, int v)
    {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int p = lg; p >= 0; p--)
            if (!is_ancestor(up[u][p], v))
                u = up[u][p];
        return up[u][0];
    }
};
