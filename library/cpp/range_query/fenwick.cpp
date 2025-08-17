template <typename T, typename C>
struct fenwick {
  vector<T> tree;
  C combine;
  fenwick(int n, T v, C combine) : tree(n + 1, v), combine(combine) {}
  void update(int i, T v) { // one-indexed
    for (; i < tree.size(); i += i & -i)
      tree[i] = combine(tree[i], v);
  }
  T query(int i) { // one-indexed
    T ans = tree[0];
    for (; i > 0; i -= i & -i)
      ans = combine(ans, tree[i]);
    return ans;
  }
};