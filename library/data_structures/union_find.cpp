template <typename F = decltype([](int, int, bool) {})>
struct union_find {
  vector<int> par, size;
  F f;
  union_find(int n, F f = {}) : par(n), size(n, 1), f(f) {
    iota(par.begin(), par.end(), 0);
  }
  int find(int i) {
    return par[i] == i ? i : find(par[i]);
  }
  template <typename... Args>
  bool unite(int i, int j, Args &&...args) {
    i = find(i), j = find(j);
    if (i == j)
      return false;
    bool swapped = false;
    if (size[i] < size[j]) {
      swap(i, j);
      swapped = true;
    }
    f(i, j, swapped, std::forward<Args>(args)...);
    size[i] += size[j];
    par[j] = i;
    return true;
  }
};