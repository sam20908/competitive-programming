/**
 * @brief Manages and unite different groups.
 *        Note that this implementation uses size rather than ranks because size is a much more useful data.
 */
template <typename F = decltype([](int, int, bool) {})>
class union_find {
  vector<int> par, sz;
  F fn;

public:
  /**
   * @brief Construct an Union Find object with `n` initial groups.
   *
   * @param n Number of initla groups.
   * @param fn Merge function to merge two components. Called as `fn(i, j, swapped, *unite-args*)`.
   */
  union_find(int n, F fn = {}) : par(n), sz(n, 1), fn(fn) {
    iota(par.begin(), par.end(), 0);
  }

  /**
   * @brief Find the parent of given group.
   *
   * @param i Index of the group.
   * @return Parent of group `i`.
   */
  int find(int i) const {
    return par[i] == i ? i : find(par[i]);
  }

  /**
   * @brief Find the size of the given group.
   *
   * @param i Index of the group.
   * @return Size of group `i`.
   */
  int size(int i) const {
    return sz[find(i)];
  }

  /**
   * @brief Unite the two given groups.
   *
   * @param i Index of the first group.
   * @param j Index of the second group.
   * @param args Additional arguments for *fn*.
   * @return Whether the merge happened (`false` if they are already in the same group).
   */
  bool unite(int i, int j, auto &&...args) {
    i = find(i), j = find(j);
    if (i == j)
      return false;
    bool swapped = false;
    if (sz[i] < sz[j]) {
      swap(i, j);
      swapped = true;
    }
    fn(i, j, swapped, args...);
    sz[i] += sz[j];
    par[j] = i;
    return true;
  }
};