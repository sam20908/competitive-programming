template <typename T, typename A, typename C, typename C2, typename F = identity>
struct segment_tree {
  vector<T> tree;
  A apply;
  C combine;
  C2 query_combine;
  F query_fn;
  segment_tree(int n, T v, A apply, C combine, C2 query_combine, F query_fn = {}) : tree(2 * n, v), apply(apply), combine(combine), query_combine(query_combine), query_fn(query_fn) {}
  template <typename... Args>
  void update(int i, Args &&...args) {
    int n = tree.size() >> 1;
    for (apply(tree[i += n], std::forward<Args>(args)...); i >>= 1;)
      tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
  }
  template <typename R = T, typename... Args>
  R query(int l, int r, R ans = {}, Args &&...args) { // [l, r)
    int n = tree.size() >> 1;
    auto ansl = ans, ansr = ans;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = query_combine(ansl, query_fn(tree[l++], std::forward<Args>(args)...));
      if (r & 1)
        ansr = query_combine(query_fn(tree[--r], std::forward<Args>(args)...), ansr);
    }
    return query_combine(ansl, ansr);
  }
};