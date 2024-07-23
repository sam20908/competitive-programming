template <typename T, typename U, typename V>
struct segment_tree {
  vector<T> tree;
  U updater;
  V combiner;
  segment_tree(int n, T default_value, U updater, V combiner) : tree(2 * n, default_value), updater(updater), combiner(combiner) {}
  void update(int i, T v) {
    for (tree[i] = updater(tree[i += tree.size() >> 1], v); i >>= 1;)
      tree[i] = combiner(tree[i << 1], tree[i << 1 | 1]);
  }
  invoke_result_t<V, T, T> query(int l, int r, invoke_result_t<V, T, T> default_value) { // [l, r)
    auto ansl = default_value, ansr = default_value;
    for (l += tree.size() >> 1, r += tree.size() >> 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = combiner(ansl, tree[l++]);
      if (r & 1)
        ansr = combiner(tree[--r], ansr);
    }
    return combiner(ansl, ansr);
  }
};