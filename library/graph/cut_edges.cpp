#include <bits/stdc++.h>
using namespace std;

// adjacent neighbours is in the form of [neighbour, edge]
vector<int> find_cut_edges(int n, int m, vector<vector<pair<int, int>>> &g) {
  vector<int> ans(m), disc(n), low(n);
  int time = 0;
  auto f = [&](auto &self, int u, int p) -> int {
    int childs = 0;
    disc[u] = low[u] = ++time;
    for (auto [v, e] : g[u]) {
      if (v == p)
        continue;
      if (!disc[v]) {
        childs++;
        self(self, v, u);
        ans[e] = disc[u] < low[v];
        low[u] = min(low[u], low[v]);
      } else
        low[u] = min(low[u], disc[v]);
    }
    return childs;
  };
  for (int i = 0; i < g.size(); i++)
    if (!disc[i])
      f(f, i, i);
  return ans;
}