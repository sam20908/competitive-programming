struct union_find {
  struct info_t {
    int i; // bigger component
    int j; // smaller component
    bool swapped;
  };
  int comps;
  vector<int> v;            // size for parent and -parent otherwise
  function<void(info_t)> f; // FIXME: Use function_ref in C++26
  union_find(int n, function<void(info_t)> f = {}) : comps(n), v(n, 1), f(std::move(f)) {}
  int find(int i) {
    return v[i] > 0 ? i : -(v[i] = -find(-v[i]));
  }
  int size(int i) {
    return v[find(i)];
  }
  bool unite(int i, int j) {
    i = find(i), j = find(j);
    if (i == j)
      return false;
    comps--;
    bool swapped = false;
    if (v[i] < v[j]) {
      swap(i, j);
      swapped = true;
    }
    if (f) {
      f({i, j, swapped});
    }
    v[i] += v[j];
    v[j] = -i;
    return true;
  }
};