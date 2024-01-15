#include <bits/stdc++.h>
using namespace std;

struct lowest_common_ancestor {
  int lg = 0;
  vector<vector<int>> dp;
  vector<int> in, out;
  lowest_common_ancestor(int n, vector<vector<int>> &g, int root)
      : lg(__lg(n)), dp(lg + 1, vector<int>(n)), in(n), out(n) {
    int time = 0;
    auto f = [&](auto &self, int u, int p) -> void {
      in[u] = ++time;
      dp[0][u] = p;
      for (int p = 1; p <= lg; p++) dp[p][u] = dp[p - 1][dp[u][p - 1]];
      for (int next : g[u])
        if (next != p) self(self, next, u);
      out[u] = ++time;
    };
    f(f, root, root);
  }
  bool is_ancestor(int u, int v) {
    return in[u] <= in[v] && out[u] >= out[v]; // if u is ancestor of v
  }
  int query(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int p = lg; p >= 0; p--)
      if (!is_ancestor(dp[p][u], v)) u = dp[p][u];
    return dp[0][u];
  }
};
