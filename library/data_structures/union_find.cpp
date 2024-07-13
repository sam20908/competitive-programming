struct union_find {
  vector<int> par, size;
  union_find(int n) : par(n), size(n, 1) {
    iota(par.begin(), par.end(), 0);
  }
  int find(int i) {
    return par[i] == i ? i : find(par[i]);
  }
  void unite(int i, int j, function<void(int, int)> fn = [](int, int) {}) {
    i = find(i), j = find(j);
    if (i == j)
      return;
    if (size[i] < size[j])
      swap(i, j);
    if (fn)
      fn(i, j);
    size[i] += size[j];
    par[j] = i;
  }
};