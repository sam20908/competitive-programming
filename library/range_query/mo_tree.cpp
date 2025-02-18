template <typename A, typename R, typename F>
struct mo_tree {
  vector<pair<int, int>> q;
  A add;
  R remove;
  F f;
  mo_tree(A add, R remove, F f) : add(add), remove(remove), f(f) {}
  void add_query(int l, int r) {
    q.push_back({l, r});
  };
  template <typename T = invoke_result_t<F>>
  vector<T> solve(int n, auto &&heuristic, auto &&lca) {
    int m = q.size();
    vector<pair<int, int>> q2(m);
    for (int i = 0; i < m; i++) {
      auto [u, v] = q[i];
      if (lca.start[u] > lca.start[v])
        swap(u, v);
      q2[i] = {lca.lca(u, v) == u ? lca.start[u] : lca.end[u], lca.start[v]};
    }
    auto h = heuristic(q2);
    vector<int> ord(m);
    iota(ord.begin(), ord.end(), 0);
    ranges::sort(ord, [&](int i, int j) {
      return h[i] < h[j];
    });
    vector<int> cnt(n);
    vector<T> ans(m);
    auto modify = [&](int u, int c) {
      if (c & 1)
        add(u);
      else
        remove(u);
    };
    for (int i = 0, cl = 0, cr = -1; i < m; i++) {
      auto [l, r] = q2[ord[i]];
      int u = lca.node[l], v = lca.node[r], a = lca.lca(lca.node[l], lca.node[r]);
      while (cr < r)
        ++cr, modify(lca.node[cr], ++cnt[lca.node[cr]]);
      while (l < cl)
        --cl, modify(lca.node[cl], ++cnt[lca.node[cl]]);
      while (r < cr)
        modify(lca.node[cr], --cnt[lca.node[cr]]), --cr;
      while (cl < l)
        modify(lca.node[cl], --cnt[lca.node[cl]]), ++cl;
      if (a == u)
        ans[ord[i]] = f();
      else {
        modify(a, ++cnt[a]);
        ans[ord[i]] = f();
        modify(a, --cnt[a]);
      }
    }
    return ans;
  }
};