template <typename R, typename... Args>
struct mo_tree {
  vector<pair<int, int>> q;
  vector<tuple<Args...>> args;
  function<void(int)> add, erase; // FIXME: Use function_ref in C++26
  function<R(Args...)> get_ans;
  mo_tree(function<void(int)> add, function<void(int)> remove, function<R(Args...)> get_ans) : add(std::move(add)), erase(std::move(erase)), get_ans(get_ans) {}
  void add_query(int l, int r) {
    q.push_back({l, r});
  };
  vector<R> solve(auto &&heuristic, const lowest_common_ancestor &lca) {
    int n = lca.depth.size(), m = q.size();
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
    vector<R> ans(m);
    auto modify = [&](int u, int c) {
      if (c & 1)
        add(u);
      else
        erase(u);
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
        ans[ord[i]] = get_ans();
      else {
        modify(a, ++cnt[a]);
        ans[ord[i]] = apply(get_ans, args[ord[i]]);
        modify(a, --cnt[a]);
      }
    }
    return ans;
  }
};