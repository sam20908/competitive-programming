template <invocable<int, int> F>
struct union_find {
  vector<int> par, size;
  F f;
  union_find(int n, F f) : par(n), size(n, 1), f(f) {
    iota(par.begin(), par.end(), 0);
  }
  int find(int i) {
    return par[i] == i ? i : find(par[i]);
  }
  void unite(int i, int j) {
    i = find(i), j = find(j);
    if (i == j)
      return;
    if (size[i] < size[j])
      swap(i, j);
    f(i, j);
    size[i] += size[j];
    par[j] = i;
  }
};