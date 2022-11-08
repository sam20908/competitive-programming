int time = 0;
vector<int> disc, low, ap;
int tarjan2(int u, int p) {
  int childrens = 0;
  low[u] = disc[u] = ++time;
  for (int v : adj[u]) {
    if (v == p)
      continue;
    if (!disc[v]) {
      childrens++;
      tarjan2(v, u);
      if (disc[u] <= low[v])
        ap[u] = true;
      low[u] = min(low[u], low[v]);
    } else
      low[u] = min(low[u], disc[v]);
  }
  return childrens;
}
void tarjan() {
  disc = low = ap = vec<int>(adj.size());
  for (int u = 0; u < adj.size(); u++)
    ap[u] = tarjan2(u, u) > 1;
}