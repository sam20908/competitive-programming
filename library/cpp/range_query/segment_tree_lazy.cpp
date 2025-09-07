/**
 * @brief Iterative Segment Tree with lazy propagation.
 *
 * @tparam T Value type.
 * @tparam D Update type.
 * @tparam Apply Applies delayed updates to node value with signature `Fn(value,
 * updates, interval-length) -> new-value`.
 * @tparam Push Pushes update into delayed updates with signature `Fn(updates,
 new-update, interval-length) -> combined-updates`.
 * @tparam Combine Combines two child node values with signature `Fn(value1,
 value2) -> result`.
 */
template <typename T, typename D, typename Apply, typename Push,
          typename Combine>
class segment_tree_lazy {
  vector<T> t;
  vector<D> d;
  vector<bool> f;
  Apply apply;
  Push push;
  Combine combine;
  int n0;

  void _apply(int i, const D &v, int k) {
    int n = d.size();
    t[i] = apply(t[i], v, k);
    if (i < n) {
      d[i] = push(d[i], v, k);
      f[i] = true;
    }
  }
  void _push(int p) {
    int n = d.size();
    int h = __lg(n) + 1;
    int k = 1 << (h - 1);
    for (p += n; h > 0; h--, k >>= 1) {
      int i = p >> h;
      if (f[i]) {
        _apply(i << 1, d[i], k);
        _apply(i << 1 | 1, d[i], k);
        d[i] = d[0];
        f[i] = false;
      }
    }
  }
  void _compute(int i, int k) {
    t[i] = f[i] ? apply(t[i], d[i], k) : combine(t[i << 1], t[i << 1 | 1]);
  }

public:
  segment_tree_lazy(const vector<T> &v, const D &d0, const Apply &apply,
                    const Push &push, const Combine &combine)
      : apply(apply), push(push), combine(combine) {
    n0 = v.size();
    int n2 = 1 << (__lg(n0) + int((n0 & (n0 - 1)) > 0)); // lowest pow2 >= n
    t.resize(2 * n2);
    d.resize(n2, d0);
    f.resize(n2);
    for (int i = 0; i < n0; i++)
      t[i + n2] = v[i];
    for (int i = n2 - 1; i > 0; --i)
      t[i] = combine(t[i << 1], t[i << 1 | 1]);
  }
  segment_tree_lazy(int n, const T &v, const D &d0, const Apply &apply,
                    const Push &push, const Combine &combine)
      : segment_tree_lazy(vector<T>(n, v), d0, apply, push, combine) {}

  /**
   * @brief Updates the range `[l, r)`.
   */
  void update(int l, int r, const D &v) {
    _push(l);
    _push(r - 1);
    int k = 1, n = d.size(), cl = 0, cr = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (cl)
        _compute(l - 1, k);
      if (cr)
        _compute(r, k);
      if (l & 1) {
        _apply(l++, v, k);
        cl = true;
      }
      if (r & 1) {
        _apply(--r, v, k);
        cr = true;
      }
    }
    for (--l; r > 0; l >>= 1, r >>= 1, k <<= 1) {
      if (cl)
        _compute(l, k);
      if (cr && (!cl || l != r))
        _compute(r, k);
    }
  }

  /**
   * @brief Queries the range `[l, r)`.
   */
  T query(int l, int r, const T &ans0) {
    _push(l);
    _push(r - 1);
    int n = d.size();
    T ansl = ans0, ansr = ans0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = combine(ansl, t[l++]);
      if (r & 1)
        ansr = combine(t[--r], ansr);
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
    int n = d.size();
    int i = l + n, d = 1;
    _push(l);
    for (T ans = ans0;
         l < n && ((i & 1 ^ 1) ||
                   std::invoke(std::forward<F>(f), ans = combine(ans0, t[i])));
         d <<= 1, i = (i >> 1) + (i & 1))
      if (i & 1)
        ans0 = std::move(ans), l += d;
    for (; l < n && i < 2 * n; d >>= 1) {
      _push(l);
      if (auto ans = combine(ans0, t[exchange(i, i << 1)]); f(ans))
        ans0 = std::move(ans), i += 2, l += d;
    }
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
    int n = d.size();
    int i = r + n, d = 1;
    _push(r);
    for (T ans = t[0]; r >= 0 && i > 1 &&
                       ((i & 1) || std::invoke(std::forward<F>(f),
                                               ans = combine(ans0, t[i])));
         d <<= 1, i = (i - 1) >> 1)
      if (i & 1 ^ 1)
        ans0 = std::move(ans), r -= d;
    for (; r >= 0 && i < 2 * n; r -= d, d >>= 1) {
      _push(r);
      if (auto ans =
              exchange(ans0, combine(ans0, t[exchange(i, (i << 1) - 1)]));
          !f(ans0))
        ans0 = std::move(ans), i += 2, r += d;
    }
    return r;
  }
};
