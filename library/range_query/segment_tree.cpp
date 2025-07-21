template <typename T>
struct segment_tree {
  vector<T> tree;
  function<T(T, T)> combine;
  segment_tree(int n, function<T(T, T)> combine) : tree(2 * n), combine(std::move(combine)) {
    for (int i = n - 1; i > 0; --i)
      tree[i] = this->combine(tree[i << 1], tree[i << 1 | 1]);
  }
  segment_tree(const vector<T> &v, function<T(T, T)> combine) : tree(2 * v.size()), combine(std::move(combine)) {
    int n = v.size();
    for (int i = 0; i < n; i++)
      tree[i + n] = v[i];
    for (int i = n - 1; i > 0; --i)
      tree[i] = this->combine(tree[i << 1], tree[i << 1 | 1]);
  }
  void update(int i, const T &v) {
    int n = tree.size() >> 1;
    for (tree[i += n] = combine(tree[i + n], v); i >>= 1;)
      tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
  }
  void set(int i, const T &v) {
    int n = tree.size() >> 1;
    for (tree[i += n] = v; i >>= 1;)
      tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
  }
  optional<T> query(int l, int r) { // [l, r)
    int n = tree.size() >> 1;
    optional<T> ansl, ansr;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = ansl ? combine(*ansl, tree[l++]) : tree[l++];
      if (r & 1)
        ansr = ansr ? combine(tree[--r], *ansr) : tree[--r];
    }
    return ansl && ansr ? combine(*ansl, *ansr) : ansl ? ansl : ansr;
  }
  template <typename R = T, typename F = identity>
  optional<R> query(int l, int r, function<R(R, R)> query_combine, F query_fn = {}, auto &&...args) { // [l, r)
    int n = tree.size() >> 1;
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
    int n = tree.size() >> 1, i = l + n, d = 1;
    assert((n & (n - 1)) == 0);
    optional<R> ans0;
    for (optional<R> ans; l < n && ((i & 1 ^ 1) || fn(ans = ans0 ? query_combine(*ans0, query_fn(tree[i], args...)) : query_fn(tree[i], args...))); d <<= 1, i = (i >> 1) + (i & 1))
      if (i & 1)
        ans0 = std::move(ans), l += d;
    for (; l < n && i < 2 * n; d >>= 1)
      if (auto ans = ans0 ? query_combine(*ans0, query_fn(tree[(i <<= 1) >> 1], args...)) : query_fn(tree[(i <<= 1) >> 1], args...); fn(ans))
        ans0 = std::move(ans), i += 2, l += d;
    return l;
  }
  template <typename R = T>
  int min_l(int r, auto fn, auto &&...args) { // minimum l<=r such that f(a[l+1..r]) is true
    int n = tree.size() >> 1, i = r + n, d = 1;
    assert((n & (n - 1)) == 0);
    optional<R> ans0;
    for (optional<R> ans; r >= 0 && i > 1 && ((i & 1) || fn(ans = ans0 ? query_combine(*ans0, query_fn(tree[i], args...)) : query_fn(tree[i], args...))); d <<= 1, i = (i - 1) >> 1)
      if (i & 1 ^ 1)
        ans0 = std::move(ans), r -= d;
    for (; r >= 0 && i < 2 * n; r -= d, d >>= 1)
      if (auto ans = exchange(ans0, ans0 ? query_combine(*ans0, query_fn(tree[((i = (i << 1) - 1) + 1) >> 1], args...)) : query_fn(tree[((i = (i << 1) - 1) + 1) >> 1], args...)); !fn(ans0))
        ans0 = std::move(ans), i += 2, r += d;
    return r;
  }
};
