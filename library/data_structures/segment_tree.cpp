template <typename T, invocable<T, T> U, invocable<T, T> V>
struct segment_tree {
  vector<T> tree;
  U apply;
  V merge;
  segment_tree(int n, T v, U apply, V merge) : tree(2 * n, v), apply(apply), merge(merge) {}
  void update(int i, T v) {
    for (tree[i] = apply(tree[i += tree.size() >> 1], v); i >>= 1;)
      tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
  }
  T query(int l, int r, T ans = {}) { // [l, r)
    auto ansl = ans, ansr = ans;
    for (l += tree.size() >> 1, r += tree.size() >> 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = merge(ansl, tree[l++]);
      if (r & 1)
        ansr = merge(tree[--r], ansr);
    }
    return merge(ansl, ansr);
  }
};