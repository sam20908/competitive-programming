/**
 * @brief Iterative segment tree with range update and range query.
 */
template <typename T, typename U, typename A, typename P, typename C, typename C2 = C, typename F = identity>
class segment_tree_lazy {
  vector<T> tree;
  vector<U> delay;
  A apply;
  P push;
  C combine;
  C2 query_combine;
  F query_fn;

  void apply_delay(int i, const U &v, int k) {
    int n = delay.size();
    apply(tree[i], v, k);
    if (i < n)
      push(delay[i], v, k);
  }
  void push_delay(int l, int r) {
    int n = delay.size();
    int h = __lg(n), k = 1 << __lg(n) >> 1;
    for (l += n, r += n - 1; h; h--, k >>= 1)
      for (int i = l >> h; i <= r >> h; i++)
        if (delay[i] != delay[0]) {
          apply_delay(i << 1, delay[i], k);
          apply_delay(i << 1 | 1, delay[i], k);
          delay[i] = delay[0];
        }
  }
  void lift(int l, int r) {
    int n = delay.size();
    l += n, r += n - 1;
    for (int k = 2; l > 1; k <<= 1, l >>= 1)
      for (int i = r >>= 1; i >= l >> 1; i--) {
        tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
        if (delay[i] != delay[0])
          apply(tree[i], delay[i], k);
      }
  }

public:
  /**
   * @brief Construct a new segment tree and build each node.
   *
   * @param n Size of the segment tree.
   * @param v Default value for leaf nodes.
   * @param d Default value for delay nodes.
   * @param apply Applies the update argument to the tree node. Called as `fn(v, *accumulated delay*, *current node size*)`.
   * @param push Applies the update argument to the delay node. Called as `fn(v, *accumulated delay*, *current node size*)`.
   * @param combine Returns the combined value of two child nodes. Called as `fn(*left-value*, *right-value*)`.
   * @param query_combine Almost the same as `combine` but runs during queries and can take additional arguments.
   * @param query_fn Transforms a node value into another value (default to returning the same value) for `query_combine`.
   */
  segment_tree_lazy(int n, T v, U d, A apply, P push, C combine, C2 query_combine = {}, F query_fn = {}) : tree(2 * n, v), delay(n, d), apply(apply), push(push), combine(combine), query_combine(query_combine), query_fn(query_fn) {
    for (int i = n - 1; i > 0; --i)
      tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
  }

  /**
   * @brief Update the half-open interval [l,r).
   *
   * @param l Left boundary inclusive.
   * @param r Right boundary exclusive.
   * @param v Value to contribute to the interval.
   */
  void update(int l, int r, const U &v) {
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

  /**
   * @brief Query for half-open interval [l,r).
   *
   * @param l Left boundary (inclusive).
   * @param r Right boundary (exclusive).
   * @param ans0 Default answer for the query.
   * @param args Additional arguments for `query_fn`.
   * @return Answer to the query.
   */
  auto query(int l, int r, auto ans0, auto &&...args) { // [l, r)
    push_delay(l, l + 1);
    push_delay(r - 1, r);
    int n = delay.size();
    auto ansl = ans0, ansr = ans0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        ansl = query_combine(ansl, query_fn(tree[l++], args...));
      if (r & 1)
        ansr = query_combine(query_fn(tree[--r], args...), ansr);
    }
    return query_combine(ansl, ansr);
  }

  /**
   * @brief Binary searches the maximum `r` s.t. `fn(a[l..r-1])` is true.
   *
   * @param l Left boundary.
   * @param fn Monotonic boolean function.
   * @param ans0 Default answer for `fn`.
   * @param args Additional arguments for `fn`.
   * @return Maximum `r`
   */
  int max_r(int l, auto fn, auto ans0, auto &&...args) { // maximum r>=l such that f(a[l..r-1]) is true
    int n = tree.size() >> 1, i = l + n, d = 1;
    assert((n & (n - 1)) == 0);
    push_delay(l, l + 1);
    for (auto ans = ans0; l < n && ((i & 1 ^ 1) || fn(ans = query_combine(ans0, query_fn(tree[i]), args...))); d <<= 1, i = (i >> 1) + (i & 1))
      if (i & 1)
        ans0 = std::move(ans), l += d;
    for (; l < n && i < 2 * n; d >>= 1) {
      push_delay(l, l + 1);
      if (auto ans = query_combine(ans0, query_fn(tree[(i <<= 1) >> 1]), args...); fn(ans))
        ans0 = std::move(ans), i += 2, l += d;
    }
    return l;
  }

  /**
   * @brief Binary searches the minimum `l` s.t. `fn(a[l+1..r])` is true.
   *
   * @param r Right boundary.
   * @param fn Monotonic boolean function.
   * @param ans0 Default answer for `fn`.
   * @param args Additional arguments for `fn`.
   * @return Minimum `l`
   */
  int min_l(int r, auto fn, auto ans0, auto &&...args) { // minimum l<=r such that f(a[l+1..r]) is true
    int n = tree.size() >> 1, i = r + n, d = 1;
    assert((n & (n - 1)) == 0);
    push_delay(r, r + 1);
    for (auto ans = ans0; r >= 0 && i > 1 && ((i & 1) || fn(ans = query_combine(ans0, query_fn(tree[i]), args...))); d <<= 1, i = (i - 1) >> 1)
      if (i & 1 ^ 1)
        ans0 = std::move(ans), r -= d;
    for (; r >= 0 && i < 2 * n; r -= d, d >>= 1) {
      push_delay(r, r + 1);
      if (auto ans = exchange(ans0, query_combine(ans0, query_fn(tree[((i = (i << 1) - 1) + 1) >> 1]), args...)); !fn(ans0))
        ans0 = std::move(ans), i += 2, r += d;
    }
    return r;
  }
};