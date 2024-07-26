template <typename T, invocable<T, T, int> A, invocable<T, T, int> B, invocable<T, T> U>
struct segment_tree_lazy {
  vector<T> tree, delay;
  T d0;
  A apply;
  B push;
  U merge;
  segment_tree_lazy(int n, T v, T d0, A apply, B push, U merge) : tree(2 * n, v), delay(n, d0), d0(d0), apply(apply), push(push), merge(merge) {}
  void apply_delay(int i, T v, int k) {
    tree[i] = apply(tree[i], v, k);
    if (i < delay.size())
      delay[i] = push(delay[i], v, k);
  }
  void lift(int l, int r) {
    l += delay.size(), r += delay.size() - 1;
    for (int k = 2; l > 1; k <<= 1, l >>= 1)
      for (int i = r >>= 1; i >= l >> 1; i--)
        tree[i] = delay[i] == d0 ? merge(tree[i << 1], tree[i << 1 | 1]) : apply(d0, delay[i], k);
  }
  void push_delay(int l, int r) {
    int h = __lg(delay.size()), k = 1 << __lg(delay.size()) >> 1;
    for (l += delay.size(), r += delay.size() - 1; h; h--, k >>= 1)
      for (int i = l >> h; i <= r >> h; i++)
        if (delay[i] != d0) {
          apply_delay(i << 1, delay[i], k);
          apply_delay(i << 1 | 1, delay[i], k);
          delay[i] = d0;
        }
  }
  void update(int l, int r, T v) { // [l, r)
    push_delay(l, l + 1);
    push_delay(r - 1, r);
    int l0 = l, r0 = r, k = 1;
    for (l += delay.size(), r += delay.size(); l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (l & 1)
        apply_delay(l++, v, k);
      if (r & 1)
        apply_delay(--r, v, k);
    }
    lift(l0, l0 + 1);
    lift(r0 - 1, r0);
  }
  T query(int l, int r, T ans = {}) { // [l, r)
    push_delay(l, l + 1);
    push_delay(r - 1, r);
    auto ansl = ans, ansr = ans;
    for (l += delay.size(), r += delay.size(); l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = merge(ansl, tree[l++]);
      if (r & 1)
        ansr = merge(tree[--r], ansr);
    }
    return merge(ansl, ansr);
  }
};