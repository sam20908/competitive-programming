namespace SCC
{
    vector<vector<int>> compute(vector<vector<int>> &g)
    {
        int n = g.size();
        vector<int> vis(n), order;
        order.reserve(n);
        auto dfs1 = [&](auto &self, int u) -> void
        {
            vis[u] = true;
            for (int v : g[u])
                if (!vis[v])
                    self(self, v);
            order.push_back(u);
        };
        for (int i = 0; i < n; i++)
            if (!vis[i])
                dfs1(dfs1, i);
        reverse(order.begin(), order.end());
        auto dfs2 = [&](auto &self, int u, vector<int> &cur_component) -> void
        {
            cur_component.push_back(u);
            vis[u] = false;
            for (int v : g[u])
                if (vis[v])
                    self(self, v, cur_component);
        };
        vector<vector<int>> components;
        for (int u : order)
        {
            if (vis[u])
            {
                vector<int> cur_component;
                dfs2(dfs2, u, cur_component);
                components.push_back(std::move(cur_component));
            }
        }
        return components;
    }
};