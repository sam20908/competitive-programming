struct lowest_common_ancestor {
  vector<int> tour, start, end, node, depth, mask;
  vector<vector<int>> dp;
  vector<vector<vector<int>>> blocks;
  lowest_common_ancestor(const vector<vector<int>> &g, int root = 0) {
    int n = g.size();
    tour.reserve(2 * n);
    start.resize(n);
    end.resize(n);
    node.resize(2 * n);
    depth.resize(n);
    auto dfs = [&](auto &self, int u, int p, int d) -> void {
      node[start[u] = end[u] = tour.size()] = u;
      depth[u] = d;
      tour.push_back(u);
      for (int v : g[u]) {
        if (v != p) {
          self(self, v, u, d + 1);
          tour.push_back(u);
        }
      }
      node[end[u] = tour.size()] = u;
    };
    dfs(dfs, root, root, 0);
    int m = tour.size();
    int b_size = max(1, __lg(m) >> 1);
    int b_cnt = (m + b_size - 1) / b_size;
    dp.resize(b_cnt, vector(__lg(b_cnt) + 1, 0));
    for (int i = 0, j = 0, b = 0; i < m; i++, j++) {
      if (j == b_size)
        j = 0, b++;
      if (j == 0 || min_by_depth(i, dp[b][0]) == i)
        dp[b][0] = i;
    }
    for (int l = 1; l <= __lg(b_cnt); l++) {
      for (int i = 0; i < b_cnt; i++) {
        if (int j = i + (1 << (l - 1)); j >= b_cnt)
          dp[i][l] = dp[i][l - 1];
        else
          dp[i][l] = min_by_depth(dp[i][l - 1], dp[j][l - 1]);
      }
    }
    mask.resize(b_cnt);
    for (int i = 0, j = 0, b = 0; i < m; i++, j++) {
      if (j == b_size)
        j = 0, b++;
      if (j > 0 && (i >= m || min_by_depth(i - 1, i) == i - 1))
        mask[b] += 1 << (j - 1);
    }
    blocks.resize(1 << (b_size - 1));
    for (int b = 0; b < b_cnt; b++) {
      int msk = mask[b];
      if (!blocks[msk].empty())
        continue;
      blocks[msk].resize(b_size, vector(b_size, 0));
      for (int l = 0; l < b_size; l++) {
        blocks[msk][l][l] = l;
        for (int r = l + 1; r < b_size; r++) {
          blocks[msk][l][r] = blocks[msk][l][r - 1];
          if (b * b_size + r < m)
            blocks[msk][l][r] = min_by_depth(b * b_size + blocks[msk][l][r], b * b_size + r) - b * b_size;
        }
      }
    }
  }
  int min_by_depth(int i, int j) const {
    return depth[tour[i]] < depth[tour[j]] ? i : j;
  }
  int lca_block(int b, int l, int r) const {
    int b_size = max(1, (int)__lg(tour.size()) >> 1);
    return blocks[mask[b]][l][r] + b * b_size;
  }
  int lca(int v, int u) const {
    int l = start[v], r = start[u], b_size = max(1, (int)__lg(tour.size()) >> 1);
    if (l > r)
      swap(l, r);
    int bl = l / b_size;
    int br = r / b_size;
    if (bl == br)
      return tour[lca_block(bl, l % b_size, r % b_size)];
    int ans = min_by_depth(lca_block(bl, l % b_size, b_size - 1), lca_block(br, 0, r % b_size));
    if (bl + 1 < br) {
      int l = __lg(br - bl - 1);
      ans = min_by_depth(ans, min_by_depth(dp[bl + 1][l], dp[br - (1 << l)][l]));
    }
    return tour[ans];
  }
  template <typename F>
  struct offline_path_queries {
    vector<pair<int, int>> q;
    function<void(int)> add, erase; // FIXME: Use function_ref in C++26
    F get_ans;
    offline_path_queries(function<void(int)> add, function<void(int)> remove, F get_ans) : add(std::move(add)), erase(std::move(erase)), get_ans(get_ans) {}
    void add_query(int l, int r) {
      q.push_back({l, r});
    };
    template <typename T = invoke_result_t<F>>
    vector<T> solve(auto &&heuristic, const lowest_common_ancestor &lca) {
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
      vector<T> ans(m);
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
          ans[ord[i]] = get_ans();
          modify(a, --cnt[a]);
        }
      }
      return ans;
    }
  };
};
