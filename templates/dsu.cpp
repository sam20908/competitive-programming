struct DSU {
  vector<int> parent, size;
  DSU(int n): parent(n), size(n, 1) {
    iota(parent.begin(), parent.end(), 0);
  }
  int find(int i) {
    return parent[i] == i ? i : find(parent[i]);
  }
  void unite(int i, int j) {
    i = find(i), j = find(j);
    if (i == j) return;
    if (size[i] < size[j]) swap(i, j);
    size[i] += size[j];
    parent[j] = i;
  }
};
