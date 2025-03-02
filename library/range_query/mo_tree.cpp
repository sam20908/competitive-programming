/**
 * @brief Run Mo's Algorithm to answer simple path queries offline.
 *
 * @param g Tree in adjacency list form
 * @param q List of queries
 * @param heuristic Returns an list of comparable objects dictating the order the queries will be answered.
 * @param add Adds the current element. Called as `fn(index)`.
 * @param remove Removes the current element. Called as `fn(index)`.
 * @param answer Returns the current answer.
 * @return List of answers in the corresponding index of the queries.
 */
auto mo_tree(const vector<vector<int>> &g, int root, const vector<pair<int, int>> &q, auto &&heuristic, auto &&add, auto &&remove, auto &&answer) {
  int n = g.size(), m = q.size();
  lowest_common_ancestor lca{g, root};
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
  vector<decay_t<decltype(answer())>> ans(m);
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
      ans[ord[i]] = answer();
    else {
      modify(a, ++cnt[a]);
      ans[ord[i]] = answer();
      modify(a, --cnt[a]);
    }
  }
  return ans;
}