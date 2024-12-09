template <typename T, typename U, typename A, typename P, typename C, typename C2 = C, typename F = identity>
struct segment_tree_lazy {
  vector<T> tree;
  vector<U> delay;
  U d0;
  A apply;
  P push;
  C combine;
  C2 query_combine;
  F query_fn;
  segment_tree_lazy(int n, T v, U d0, A apply, P push, C combine, C2 query_combine = {}, F query_fn = {}) : tree(2 * n, v), delay(n, d0), d0(d0), apply(apply), push(push), combine(combine), query_combine(query_combine), query_fn(query_fn) {
    for (int i = n - 1; i > 0; --i)
      tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
  }
  void apply_delay(int i, const U &v, int k) {
    int n = delay.size();
    tree[i] = apply(tree[i], v, k);
    if (i < n)
      delay[i] = push(delay[i], v, k);
  }
  void lift(int l, int r) {
    int n = delay.size();
    l += n, r += n - 1;
    for (int k = 2; l > 1; k <<= 1, l >>= 1)
      for (int i = r >>= 1; i >= l >> 1; i--) {
        tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
        if (delay[i] != d0)
          tree[i] = apply(tree[i], delay[i], k);
      }
  }
  void push_delay(int l, int r) {
    int n = delay.size();
    int h = __lg(n), k = 1 << __lg(n) >> 1;
    for (l += n, r += n - 1; h; h--, k >>= 1)
      for (int i = l >> h; i <= r >> h; i++)
        if (delay[i] != d0) {
          apply_delay(i << 1, delay[i], k);
          apply_delay(i << 1 | 1, delay[i], k);
          delay[i] = d0;
        }
  }
  void update(int l, int r, const U &v) { // [l, r)
    push_delay(l, l + 1);
    push_delay(r - 1, r);
    int l0 = l, r0 = r, k = 1, n = delay.size();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (l & 1)
        apply_delay(l++, v, k);
      if (r & 1)
        apply_delay(--r, v, k);
    }
    lift(l0, l0 + 1);
    lift(r0 - 1, r0);
  }
  template <typename R = T, typename... Args>
  R query(int l, int r, R ans0, Args &&...args) { // [l, r)
    push_delay(l, l + 1);
    push_delay(r - 1, r);
    int n = delay.size();
    auto ansl = ans0, ansr = ans0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = query_combine(ansl, query_fn(tree[l++], std::forward<Args>(args)...));
      if (r & 1)
        ansr = query_combine(query_fn(tree[--r], std::forward<Args>(args)...), ansr);
    }
    return query_combine(ansl, ansr);
  }
};