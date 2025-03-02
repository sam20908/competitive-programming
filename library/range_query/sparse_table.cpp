/**
 * @brief Answers all queries either in O(log n) or specialized queries in O(1).
 */
template <typename T, typename C>
class sparse_table {
  vector<vector<T>> dp;
  C combine;

public:
  /**
   * @brief Construct an empty sparse table.
   *
   * @param v
   * @param combine
   */
  sparse_table(vector<T> &v, C combine) : combine(combine) {
    int n = v.size();
    dp.resize(__lg(n) + 1, vector<T>(n));
    dp[0] = v;
    for (int i = 1; i <= __lg(v.size()); i++)
      for (int j = 0; j + (1 << i) <= v.size(); j++)
        dp[i][j] = combine(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
  }

  /**
   * @brief Query the range of a sparse table in O(log n).
   *
   * @param l Left boundary inclusive
   * @param r Right boundary inclusive
   * @param ans Default answer for the query
   * @return Answer to the query
   */
  auto query(int l, int r, auto ans) {
    for (int i = dp[0].size(); i >= 0; i--)
      if ((1 << i) <= r - l + 1) {
        ans = combine(ans, dp[i][l]);
        l += 1 << i;
      }
    return ans;
  }

  /**
   * @brief Query the range of a sparse table in O(1).
   *        As the method name implies, the operation has to be idempotent.
   *
   * @param l Left boundary inclusive
   * @param r Right boundary inclusive
   * @return Answer to the query
   */
  auto query_idempotent(int l, int r) {
    int i = __lg(r - l + 1);
    return combine(dp[i][l], dp[i][r - (1 << i) + 1]);
  }
};