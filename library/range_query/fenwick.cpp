/**
 * @brief Efficient data structure with point update and prefix query. Data must be cumulative!
 *        It is a very efficient alternative to Segment Trees with additional restrictions.
 */
template <typename T, typename C>
class fenwick {
  vector<T> tree;
  C combine;

public:
  /**
   * @brief Construct a Fenwick Tree
   *
   * @param n Number of elements
   * @param v Default value
   * @param combine Function to combine values of two child nodes. Called as `fn(v1,v2)`.
   */
  fenwick(int n, T v, C combine) : tree(n + 1, v), combine(combine) {}

  /**
   * @brief Update a value at the given index.
   *
   * @param i Index to update (1-indexed!)
   * @param v Value to be combined with existing value in the tree
   */
  void update(int i, T v) {
    for (; i < tree.size(); i += i & -i)
      tree[i] = combine(tree[i], v);
  }

  /**
   * @brief Query the prefix a[1..i].
   *
   * @param i Right boundary of the prefix (1-indexed!)
   * @param ans Default answer of the query
   * @return Answer to the query
   */
  T query(int i, T ans) const {
    for (; i > 0; i -= i & -i)
      ans = combine(ans, tree[i]);
    return ans;
  }
};