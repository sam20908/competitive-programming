#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Answers subarray queries in `O(log N)` (or `O(1)` if the operation is
 * idempotent) with `O(N log N)` preprocessing.
 *
 * Sparse Tables work well when the input data stays constant. The main benefit
 * is the constant factor is very low.
 *
 * @tparam T Value type.
 * @tparam F Binary functor to merge two values.
 */
template <typename T, typename F> class sparse_table {
  vector<vector<T>> dp;
  F f;

public:
  /**
   * @brief Constructs a Sparse Table for a given array.
   */
  sparse_table(vector<T> &v, const F &f) : f(f) {
    int n = v.size();
    dp.resize(__lg(n) + 1, vector<T>(n));
    dp[0] = v;
    for (int i = 1; i <= __lg(v.size()); i++)
      for (int j = 0; j + (1 << i) <= v.size(); j++)
        dp[i][j] = f(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
  }

  /**
   * @brief Queries the range `[l, r]` in `O(log N)`.
   *
   * @param l Left bound.
   * @param r Right bound.
   */
  optional<T> query(int l, int r) const {
    optional<T> ans;
    for (int i = dp.size(); i >= 0; i--)
      if ((1 << i) <= r - l + 1) {
        ans = ans ? f(*ans, dp[i][l]) : dp[i][l];
        l += 1 << i;
      }
    return ans;
  }

  /**
   * @brief Queries the range `[l, r]` in `O(1)`.
   *
   * @param l Left bound.
   * @param r Right bound.
   */
  optional<T> query_idempotent(int l, int r) const {
    int i = __lg(r - l + 1);
    return f(dp[i][l], dp[i][r - (1 << i) + 1]);
  }
};
