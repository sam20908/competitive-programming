template <typename T, typename Combine> class segment_tree {
  vector<T> t;
  Combine combine;
  int n0;

public:
  segment_tree(int n, const T &v, const Combine &combine)
      : segment_tree(vector<T>(n, v), combine) {}
  segment_tree(const vector<T> &v, const Combine &combine) : combine(combine) {
    n0 = v.size();
    int n2 = 1 << (__lg(n0) + int((n0 & (n0 - 1)) > 0)); // lowest pow2 >= n
    t.resize(2 * n2);
    for (int i = 0; i < n0; i++)
      t[i + n2] = v[i];
    for (int i = n2 - 1; i > 0; --i)
      t[i] = combine(t[i << 1], t[i << 1 | 1]);
  }

  /**
   * @brief Update the value at the index.
   */
  void update(int i, const T &v) {
    int n = t.size() >> 1;
    for (t[i += n] = combine(t[i + n], v); i >>= 1;)
      t[i] = combine(t[i << 1], t[i << 1 | 1]);
  }

  /**
   * @brief Sets the value at the index.
   */
  void set(int i, const T &v) {
    int n = t.size() >> 1;
    for (t[i += n] = v; i >>= 1;)
      t[i] = combine(t[i << 1], t[i << 1 | 1]);
  }

  /**
   * @brief Queries the range `[l, r)`.
   */
  T query(int l, int r, const T &ans0) { // [l, r)
    int n = t.size() >> 1;
    T ansl = ans0, ansr = ans0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = ansl ? combine(ansl, t[l++]) : t[l++];
      if (r & 1)
        ansr = ansr ? combine(t[--r], ansr) : t[--r];
    }
    return combine(ansl, ansr);
  }

  /**
   * @brief Find maximum `r>=l` s.t. `f(a[l..r-1])` remains true.
   *
   * @param l Left bound.
   * @param f Predicate callable on node value.
   * @param ans0 Default answer for nodes.
   */
  template <typename F> int max_r(int l, F &&f, T ans0) {
    int n = t.size() >> 1;
    int i = l + n, d = 1;
    for (T ans = ans0;
         l < n && ((i & 1 ^ 1) ||
                   std::invoke(std::forward<F>(f), ans = combine(ans0, t[i])));
         d <<= 1, i = (i >> 1) + (i & 1))
      if (i & 1)
        ans0 = std::move(ans), l += d;
    for (; l < n && i < 2 * n; d >>= 1)
      if (auto ans = combine(ans0, t[exchange(i, i << 1)]); f(ans))
        ans0 = std::move(ans), i += 2, l += d;
    return min(l, n0);
  }

  /**
   * @brief Find minimum `l<=r` s.t. `f(a[l+1..r])` remains true.
   *
   * @param r Right bound.
   * @param f Predicate callable on node value.
   * @param ans0 Default answer for nodes.
   */
  template <typename F> int min_l(int r, F &&f, T ans0) {
    int n = t.size() >> 1;
    int i = r + n, d = 1;
    for (T ans = t[0]; r >= 0 && i > 1 &&
                       ((i & 1) || std::invoke(std::forward<F>(f),
                                               ans = combine(ans0, t[i])));
         d <<= 1, i = (i - 1) >> 1)
      if (i & 1 ^ 1)
        ans0 = std::move(ans), r -= d;
    for (; r >= 0 && i < 2 * n; r -= d, d >>= 1)
      if (auto ans =
              exchange(ans0, combine(ans0, t[exchange(i, (i << 1) - 1)]));
          !f(ans0))
        ans0 = std::move(ans), i += 2, r += d;
    return r;
  }
};
