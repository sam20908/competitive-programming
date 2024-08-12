template <typename T, typename A, typename C, typename C2>
struct segment_tree {
  vector<T> tree;
  A apply;
  C combine;
  C2 query_combine;
  segment_tree(int n, T v, A apply, C combine, C2 query_combine) : tree(2 * n, v), apply(apply), combine(combine), query_combine(query_combine) {}
  void update(int i, T v) {
    for (tree[i] = apply(tree[i += tree.size() >> 1], v); i >>= 1;)
      tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
  }
  template <bool Commutative = true, typename R = T, typename... Args>
  R query(int l, int r, R ans = {}, Args &&...args) { // [l, r)
    if constexpr (Commutative) {
      for (l += tree.size() >> 1, r += tree.size() >> 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
          ans = query_combine(ans, tree[l++], std::forward<Args>(args)...);
        if (r & 1)
          ans = query_combine(ans, tree[--r], std::forward<Args>(args)...);
      }
      return ans;
    } else {
      auto ansl = ans, ansr = ans;
      for (l += tree.size() >> 1, r += tree.size() >> 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
          ansl = query_combine(ansl, tree[l++], std::forward<Args>(args)...);
        if (r & 1)
          ansr = query_combine(tree[--r], ansr, std::forward<Args>(args)...);
      }
      return query_combine(ansl, ansr, std::forward<Args>(args)...);
    }
  }
};