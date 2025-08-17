template <typename T, typename D>
struct segment_tree_lazy {
  vector<T> tree;
  vector<optional<D>> delay;
  function<T(T, D, int)> apply;
  function<D(D, D, int)> push;
  function<T(T, T)> combine;
  segment_tree_lazy(unsigned int n, function<T(T, D, int)> apply, function<D(D, D, int)> push, function<T(T, T)> combine) : tree(2 * bit_ceil(n)), delay(bit_ceil(n)), apply(std::move(apply)), push(std::move(push)), combine(std::move(combine)) {
    for (int i = (int)delay.size() - 1; i > 0; --i)
      tree[i] = this->combine(tree[i << 1], tree[i << 1 | 1]);
  }
  void _apply_delay(int i, const D &v, int k) {
    tree[i] = apply(tree[i], v, k);
    if (i < (int)delay.size())
      delay[i] = delay[i] ? push(*delay[i], v, k) : v;
  }
  void _push_delay(int l, int r) {
    int n = delay.size();
    int h = __lg(n), k = 1 << __lg(n) >> 1;
    for (l += n, r += n - 1; h; h--, k >>= 1)
      for (int i = l >> h; i <= r >> h; i++)
        if (delay[i]) {
          _apply_delay(i << 1, *delay[i], k);
          _apply_delay(i << 1 | 1, *delay[i], k);
          delay[i] = nullopt;
        }
  }
  void _compute_value(int i, int k) {
    tree[i] = delay[i] ? apply(tree[i], *delay[i], k) : combine(tree[i << 1], tree[i << 1 | 1]);
  }
  void set(int i, const T &t) {
    _push_delay(i, i + 1);
    _push_delay(i - 1, i);
    tree[i += delay.size()] = t;
    for (i >>= 1; i; i >>= 1)
      tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
  }
  void update(int l, int r, const D &v) { // [l, r)
    _push_delay(l, l + 1);
    _push_delay(r - 1, r);
    int k = 1, n = delay.size(), cl = 0, cr = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (cl)
        _compute_value(l - 1, k);
      if (cr)
        _compute_value(r, k);
      if (l & 1) {
        _apply_delay(l++, v, k);
        cl = true;
      }
      if (r & 1) {
        _apply_delay(--r, v, k);
        cr = true;
      }
    }
    for (--l; r > 0; l >>= 1, r >>= 1, k <<= 1) {
      if (cl)
        _compute_value(l, k);
      if (cr && (!cl || l != r))
        _compute_value(r, k);
    }
  }
  optional<T> query(int l, int r) { // [l, r)
    _push_delay(l, l + 1);
    _push_delay(r - 1, r);
    int n = delay.size();
    optional<T> ansl, ansr;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = ansl ? combine(*ansl, tree[l++]) : tree[l++];
      if (r & 1)
        ansr = ansr ? combine(tree[--r], *ansr) : tree[--r];
    }
    return ansl && ansr ? combine(*ansl, *ansr) : ansl ? ansl : ansr;
  }
  template <typename R, typename F = identity>
  optional<R> query(int l, int r, function<R(R, R)> query_combine, F query_fn = {}, auto &&...args) { // [l,r)
    _push_delay(l, l + 1);
    _push_delay(r - 1, r);
    int n = delay.size();
    optional<R> ansl, ansr;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = ansl ? query_combine(*ansl, query_fn(tree[l++], args...)) : query_fn(tree[l++], args...);
      if (r & 1)
        ansr = ansr ? query_combine(query_fn(tree[--r], args...), *ansr) : query_fn(tree[--r], args...);
    }
    return ansl && ansr ? query_combine(*ansl, *ansr) : ansl ? ansl : ansr;
  }
  template <typename R = T>
  int max_r(int l, auto fn, auto &&...args) { // maximum r>=l such that f(a[l..r-1]) is true
    int n = delay.size(), i = l + n, d = 1;
    _push_delay(l, l + 1);
    optional<R> ans0;
    for (optional<R> ans; l < n && ((i & 1 ^ 1) || fn(ans = ans0 ? query_combine(*ans0, query_fn(tree[i], args...)) : query_fn(tree[i], args...))); d <<= 1, i = (i >> 1) + (i & 1))
      if (i & 1)
        ans0 = std::move(ans), l += d;
    for (; l < n && i < 2 * n; d >>= 1) {
      _push_delay(l, l + 1);
      if (auto ans = ans0 ? query_combine(*ans0, query_fn(tree[(i <<= 1) >> 1], args...)) : query_fn(tree[(i <<= 1) >> 1], args...); fn(ans))
        ans0 = std::move(ans), i += 2, l += d;
    }
    return l;
  }
  template <typename R = T>
  int min_l(int r, auto fn, auto &&...args) { // minimum l<=r such that f(a[l+1..r]) is true
    int n = delay.size(), i = r + n, d = 1;
    _push_delay(r, r + 1);
    optional<R> ans0;
    for (optional<R> ans; r >= 0 && i > 1 && ((i & 1) || fn(ans = ans0 ? query_combine(*ans0, query_fn(tree[i], args...)) : query_fn(tree[i], args...))); d <<= 1, i = (i - 1) >> 1)
      if (i & 1 ^ 1)
        ans0 = std::move(ans), r -= d;
    for (; r >= 0 && i < 2 * n; r -= d, d >>= 1) {
      _push_delay(r, r + 1);
      if (auto ans = exchange(ans0, ans0 ? query_combine(*ans0, query_fn(tree[((i = (i << 1) - 1) + 1) >> 1], args...)) : query_fn(tree[((i = (i << 1) - 1) + 1) >> 1], args...)); !fn(ans0))
        ans0 = std::move(ans), i += 2, r += d;
    }
    return r;
  }
};
