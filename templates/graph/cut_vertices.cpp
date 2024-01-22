#include <bits/stdc++.h>
using namespace std;

vector<int> find_cut_vertices(int n, int m, vector<vector<int>> &g) {
  vector<int> ans(n), disc(n), low(n);
  int time = 0;
  auto f = [&](auto &self, int u, int p) -> int {
    int childs = 0;
    disc[u] = low[u] = ++time;
    for (auto v : g[u]) {
      if (v == p)
        continue;
      if (!disc[v]) {
        childs++;
        self(self, v, u);
        ans[u] = disc[u] <= low[v];
        low[u] = min(low[u], low[v]);
      } else
        low[u] = min(low[u], disc[v]);
    }
    return childs;
  };
  for (int i = 0; i < g.size(); i++)
    if (!disc[i])
      ans[i] = f(f, i, i) > 1;
  return ans;
}