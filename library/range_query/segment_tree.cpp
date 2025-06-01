template <typename T, typename A, typename C, typename C2 = C, typename F = identity>
struct segment_tree {
  vector<T> tree;
  A apply;
  C combine;
  C2 query_combine;
  F query_fn;
  segment_tree(int n, T v, A apply, C combine, C2 query_combine = {}, F query_fn = {}) : tree(2 * n, v), apply(apply), combine(combine), query_combine(query_combine), query_fn(query_fn) {
    for (int i = n - 1; i > 0; --i)
      tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
  }
  template <typename... Args>
  void update(int i, auto &&...args) {
    int n = tree.size() >> 1;
    for (tree[i += n] = apply(tree[i + n], args...); i >>= 1;)
      tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
  }
  template <typename R = T>
  R query(int l, int r, R ans0, auto &&...args) { // [l, r)
    int n = tree.size() >> 1;
    auto ansl = ans0, ansr = ans0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = query_combine(ansl, query_fn(tree[l++], args...));
      if (r & 1)
        ansr = query_combine(query_fn(tree[--r], args...), ansr);
    }
    return query_combine(ansl, ansr);
  }
  template <typename R = T>
  int max_r(int l, auto fn, R ans0, auto &&...args) { // maximum r>=l such that f(a[l..r-1]) is true
    int n = tree.size() >> 1, i = l + n, d = 1;
    assert((n & (n - 1)) == 0);
    for (R ans; l < n && ((i & 1 ^ 1) || fn(ans = query_combine(ans0, query_fn(tree[i]), args...))); d <<= 1, i = (i >> 1) + (i & 1))
      if (i & 1)
        ans0 = std::move(ans), l += d;
    for (; l < n && i < 2 * n; d >>= 1)
      if (auto ans = query_combine(ans0, query_fn(tree[(i <<= 1) >> 1]), args...); fn(ans))
        ans0 = std::move(ans), i += 2, l += d;
    return l;
  }
  template <typename R = T>
  int min_l(int r, auto fn, R ans0, auto &&...args) { // minimum l<=r such that f(a[l+1..r]) is true
    int n = tree.size() >> 1, i = r + n, d = 1;
    assert((n & (n - 1)) == 0);
    for (R ans; r >= 0 && i > 1 && ((i & 1) || fn(ans = query_combine(ans0, query_fn(tree[i]), args...))); d <<= 1, i = (i - 1) >> 1)
      if (i & 1 ^ 1)
        ans0 = std::move(ans), r -= d;
    for (; r >= 0 && i < 2 * n; r -= d, d >>= 1)
      if (auto ans = exchange(ans0, query_combine(ans0, query_fn(tree[((i = (i << 1) - 1) + 1) >> 1]), args...)); !fn(ans0))
        ans0 = std::move(ans), i += 2, r += d;
    return r;
  }
};