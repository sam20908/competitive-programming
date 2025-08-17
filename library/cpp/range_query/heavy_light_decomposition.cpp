template <typename T>
struct heavy_light_decomposition {
  vector<int> top, depth, id, par;
  segment_tree<T> seg;
  function<T(T, T)> combine;
  void _init(const vector<vector<int>> &g, int root) {
    int n = g.size();
    vector<int> size(n, 1);
    top.resize(n);
    depth.resize(n);
    id.resize(n);
    par.resize(n);
    auto dfs = [&](auto &&self, int u, int p) -> int {
      par[u] = p;
      depth[u] = depth[p] + 1;
      for (int v : g[u])
        if (v != p)
          size[u] += self(self, v, u);
      return size[u];
    };
    dfs(dfs, root, root);
    auto dfs2 = [&, time = 0](auto &&self, int u, int p, int t) mutable -> void {
      top[u] = t;
      id[u] = time++;
      int hvy_v = -1, hvy_s = -1;
      for (int v : g[u])
        if (v != p && size[v] > hvy_s) {
          hvy_v = v;
          hvy_s = size[v];
        }
      if (hvy_v == -1)
        return;
      self(self, hvy_v, u, t);
      for (int v : g[u])
        if (v != p && v != hvy_v)
          self(self, v, u, v);
    };
    dfs2(dfs2, root, root, root);
  }

  heavy_light_decomposition(const vector<vector<int>> &g, function<T(T, T)> combine, int root = 0) : seg(g.size(), combine), combine(std::move(combine)) {
    _init(g, root);
  }
  heavy_light_decomposition(const vector<vector<int>> &g, function<T(T, T)> combine, const vector<T> &v, int root = 0) : seg(v, combine), combine(std::move(combine)) {
    _init(g, root);
    for (int i = 0; i < v.size(); i++)
      seg.set(id[i], v[i]);
  }
  void update(int a, const T &v) {
    seg.update(id[a], v);
  }
  void set(int a, const T &v) {
    seg.set(id[a], v);
  }
  optional<T> query(int a, int b) {
    optional<T> ans;
    for (; top[a] != top[b]; a = par[top[a]]) {
      if (depth[top[a]] < depth[top[b]])
        swap(a, b);
      auto res = seg.query(id[top[a]], id[a] + 1);
      ans = ans ? combine(*ans, *res) : res;
    }
    if (depth[a] > depth[b])
      swap(a, b);
    auto res = seg.query(id[a], id[b] + 1);
    ans = ans ? combine(*ans, *res) : res;
    return ans;
  }
};
