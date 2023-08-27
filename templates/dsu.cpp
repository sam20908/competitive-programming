struct dsu {
  vector<int> parent, size;
  dsu(int n) : parent(n), size(n, 1) { iota(parent.begin(), parent.end(), 0); }
  int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
  }
  void unite(int i, int j) {
    if (find(i) != find(j)) {
      int repi = find(i);
      int repj = find(j);
      if (size[repi] < size[repj]) swap(repi, repj);
      size[repi] += size[repj];
      parent[repj] = repi;
    }
  }
};