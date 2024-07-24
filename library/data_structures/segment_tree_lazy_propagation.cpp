template <typename T, typename L, typename A, typename B, typename U, typename V>
struct segment_tree {
  L default_lazy;
  vector<T> tree;
  vector<L> lazy;
  A updater;
  B propagater;
  U merger;
  V lazy_ans;
  segment_tree(int n, T default_value, L default_lazy, A updater, B propagater, U merger, V lazy_ans) : default_lazy(default_lazy), tree(2 * n, default_value), lazy(n, default_lazy), updater(updater), propagater(propagater), merger(merger), lazy_ans(lazy_ans) {}
  void apply(int i, T v, int k) {
    tree[i] = updater(tree[i], v, k);
    if (i < lazy.size())
      lazy[i] = propagater(lazy[i], v, k);
  }
  void build(int l, int r) {
    l += lazy.size(), r += lazy.size() - 1;
    for (int k = 2; l > 1; k <<= 1) {
      l >>= 1, r >>= 1;
      for (int i = r; i >= l; i--)
        if (lazy[i] == default_lazy)
          tree[i] = merger(tree[i << 1], tree[i << 1 | 1]);
        else
          tree[i] = lazy_ans(lazy[i], k);
    }
  }
  void push(int l, int r) {
    int h = __lg(lazy.size()), k = __lg(lazy.size()) >> 1;
    for (l += lazy.size(), r += lazy.size() - 1; h; h--, k >>= 1)
      for (int i = l >> h; i <= r >> h; i++)
        if (lazy[i] != default_lazy) {
          apply(i << 1, lazy[i], k);
          apply(i << 1 | 1, lazy[i], k);
          lazy[i] = default_lazy;
        }
  }
  void update(int l, int r, T v) { // [l, r)
    push(l, l + 1);
    push(r - 1, r);
    int l0 = l, r0 = r, k = 1;
    for (l += lazy.size(), r += lazy.size(); l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (l & 1)
        apply(l++, v, k);
      if (r & 1)
        apply(--r, v, k);
    }
    build(l0, l0 + 1);
    build(r0 - 1, r0);
  }
  invoke_result_t<V, T, T> query(int l, int r, invoke_result_t<V, T, T> default_value = {}) { // [l, r)
    push(l, l + 1);
    push(r - 1, r);
    auto ansl = default_value, ansr = default_value;
    for (l += lazy.size(), r += lazy.size(); l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = merger(ansl, tree[l++]);
      if (r & 1)
        ansr = merger(tree[--r], ansr);
    }
    return merger(ansl, ansr);
  }
};