/**
 * @brief Iterative segment tree with point update and range query.
 */
template <typename T, typename A, typename C, typename C2 = C, typename F = identity>
class segment_tree {
  vector<T> tree;
  A apply;
  C combine;
  C2 query_combine;
  F query_fn;

public:
  /**
   * @brief Construct a new segment tree and build each node.
   *
   * @param n Size of the segment tree.
   * @param v Default value for leaf nodes.
   * @param apply Applies the updated value to a leaf node. Called as `fn(v, *update-args*)`.
   * @param combine Returns the combined value of two child nodes. Called as `fn(*left-value*, *right-value*)`.
   * @param query_combine Almost the same as `combine` but runs during queries and can take additional arguments.
   * @param query_fn Transforms a node value into another value (default to returning the same value) for `query_combine`.
   */
  segment_tree(int n, T v, A apply, C combine, C2 query_combine = {}, F query_fn = {}) : tree(2 * n, v), apply(apply), combine(combine), query_combine(query_combine), query_fn(query_fn) {
    for (int i = n - 1; i > 0; --i)
      tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
  }

  /**
   * @brief Updates the value at the given index.
   *
   * @param i Index of the element.
   * @param args Arguments for `apply`.
   */
  void update(int i, auto &&...args) {
    int n = tree.size() >> 1;
    for (apply(tree[i += n], args...); i >>= 1;)
      tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
  }

  /**
   * @brief Queries the tree for half-open interval [l,r).
   *
   * @param l Left boundary inclusive.
   * @param r Right boundary exclusive.
   * @param ans0 Default answer for the query.
   * @param args Additional arguments for `query_fn`.
   * @return Answer to the query.
   */
  auto query(int l, int r, auto ans0, auto &&...args) const {
    int n = tree.size() >> 1;
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
   * @param ans0 Default answer for `query_combine`.
   * @param args Additional arguments for `fn`.
   * @return Maximum `r`.
   */
  int max_r(int l, auto fn, auto ans0, auto &&...args) const {
    int n = tree.size() >> 1, i = l + n, d = 1;
    assert((n & (n - 1)) == 0);
    for (auto ans = ans0; l < n && ((i & 1 ^ 1) || fn(ans = query_combine(ans0, query_fn(tree[i]), args...))); d <<= 1, i = (i >> 1) + (i & 1))
      if (i & 1)
        ans0 = std::move(ans), l += d;
    for (; l < n && i < 2 * n; d >>= 1)
      if (auto ans = query_combine(ans0, query_fn(tree[(i <<= 1) >> 1]), args...); fn(ans))
        ans0 = std::move(ans), i += 2, l += d;
    return l;
  }

  /**
   * @brief Binary searches the minimum `l` s.t. `fn(a[l+1..r])` is true.
   *
   * @param r Right boundary.
   * @param fn Monotonic boolean function.
   * @param ans0 Default answer for `query_combine`.
   * @param args Additional arguments for `fn`.
   * @return Minimum `l`.
   */
  int min_l(int r, auto fn, auto ans0, auto &&...args) const {
    int n = tree.size() >> 1, i = r + n, d = 1;
    assert((n & (n - 1)) == 0);
    for (auto ans = ans0; r >= 0 && i > 1 && ((i & 1) || fn(ans = query_combine(ans0, query_fn(tree[i]), args...))); d <<= 1, i = (i - 1) >> 1)
      if (i & 1 ^ 1)
        ans0 = std::move(ans), r -= d;
    for (; r >= 0 && i < 2 * n; r -= d, d >>= 1)
      if (auto ans = exchange(ans0, query_combine(ans0, query_fn(tree[((i = (i << 1) - 1) + 1) >> 1]), args...)); !fn(ans0))
        ans0 = std::move(ans), i += 2, r += d;
    return r;
  }
};