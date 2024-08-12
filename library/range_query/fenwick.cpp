template <typename T, typename M>
struct fenwick {
  vector<T> tree;
  M merge;
  fenwick(int n, T v, M merge) : tree(n + 1, v), merge(merge) {}
  void update(int i, T v) { // one-indexed
    for (; i < tree.size(); i += i & -i)
      tree[i] = merge(tree[i], v);
  }
  T query(int i, T ans = {}) { // one-indexed
    for (; i > 0; i -= i & -i)
      ans = merge(ans, tree[i]);
    return ans;
  }
};