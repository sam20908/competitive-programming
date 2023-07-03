struct dsu {
  vector<int> parent, rank;
  dsu(int n) : parent(n), rank(n, 1) { iota(parents.begin(), parents.end(), 0); }
  int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
  }
  void unite(int i, int j) {
    if (find(i) != find(j)) {
      int repi = find(i);
      int repj = find(j);
      if (rank[repi] < rank[repj]) swap(repi, repj);
      rank[repi] += int(rank[repi] == rank[repj]);
      parent[repj] = repi;
    }
  }
};