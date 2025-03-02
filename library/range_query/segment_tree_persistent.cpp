/**
 * @brief Persistent segment tree that supports large intervals.
 */
template <typename T, typename A, typename C, typename C2 = C, typename F = identity>
class segment_tree_persistent {
  struct node_t {
    node_t *l = nullptr, *r = nullptr;
    T v;
  };
  node_t *root0;
  int n;
  A apply;
  C combine;
  C2 query_combine;
  F query_fn;

public:
  /**
   * @brief Construct an empty persistent segment tree.
   *
   * @param n Size of the segment tree.
   * @param v Default value for leaf nodes.
   * @param apply Applies the update value to a leaf node. Called as `fn(v, *update-args*)`.
   * @param combine Returns the combined value of two child nodes. Called as `fn(*left-value*, *right-value*)`.
   * @param query_combine Almost the same as `combine` but runs during queries and can take additional arguments.
   * @param query_fn Transforms a node value into another value (default to returning the same value) for `query_combine`.
   */
  segment_tree_persistent(int n, T v, A apply, C combine, C2 query_combine = {}, F query_fn = {}) : n(n), apply(apply), combine(combine), query_combine(query_combine), query_fn(query_fn) {
    auto dfs = [&](auto &self, int tl, int tr) -> node_t * {
      if (tl == tr)
        return new node_t{.v = v};
      int tm = (tl + tr) / 2;
      auto node_l = self(self, tl, tm), node_r = self(self, tm + 1, tr);
      return new node_t{node_l, node_r, combine(node_l->v, node_r->v)};
    };
    root0 = dfs(dfs, 0, n - 1);
  }

  /**
   * @brief Returns the root of the tree after the constructor built it.
   *
   * @return The initial root.
   */
  const node_t *root() const {
    return root0;
  }

  /**
   * @brief Update the tree with the given root at given index.
   *
   * @param root Current root of the tree.
   * @param i Index to update.
   * @param args Arguments for `apply`.
   * @return New root with the modification.
   */
  node_t *update(const node_t *root, int i, auto &&...args) const {
    auto dfs = [&](auto &self, node_t *cur, int tl, int tr) -> node_t * {
      if (tl == tr) {
        auto node = new node_t{.v = cur->v};
        apply(node->v, args...);
        return node;
      }
      int tm = (tl + tr) / 2;
      auto node_l = i <= tm ? self(self, cur->l, tl, tm) : cur->l;
      auto node_r = i > tm ? self(self, cur->r, tm + 1, tr) : cur->r;
      return new node_t{node_l, node_r, combine(node_l->v, node_r->v)};
    };
    return dfs(dfs, root, 0, n - 1);
  }

  /**
   * @brief Query the range [l,r] within the tree with the given root.
   *
   * @param root Current root of the tree.
   * @param l Left boundary inclusive.
   * @param r Right boundary inclusive.
   * @param ans0 Default answer for the query.
   * @param args Additional arguments for `query_fn`.
   * @return Answer to the query.
   */
  auto query(node_t *root, int l, int r, auto ans0, auto &&...args) const { // [l, r]
    auto dfs = [&](auto &self, node_t *cur, int tl, int tr, int l, int r) -> auto {
      if (l > r)
        return ans0;
      if (tl == l && tr == r)
        return query_fn(cur->v, args...);
      int tm = (tl + tr) / 2;
      return query_combine(self(self, cur->l, tl, tm, l, min(r, tm)), self(self, cur->r, tm + 1, tr, max(l, tm + 1), r));
    };
    return dfs(dfs, root, 0, n - 1, l, r);
  }
};