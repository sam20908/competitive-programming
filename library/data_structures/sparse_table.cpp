template <typename T, invocable<T, T> U>
struct sparse_table {
  vector<vector<T>> dp;
  U merge;
  sparse_table(vector<T> &v, U merge) : dp(__lg(v.size()) + 1, vector<T>(v.size())), merge(merge) {
    dp[0] = v;
    for (int i = 1; i <= __lg(v.size()); i++)
      for (int j = 0; j + (1 << i) <= v.size(); j++)
        dp[i][j] = merge(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
  }
  T query(int l, int r, T ans = {}) {
    for (int i = dp[0].size(); i >= 0; i--)
      if ((1 << i) <= r - l + 1) {
        ans = merge(ans, dp[i][l]);
        l += 1 << i;
      }
    return ans;
  }
  T query_fast(int l, int r) { // precondition: operation is idempotent
    int i = __lg(r - l + 1);
    return merge(dp[i][l], dp[i][r - (1 << i) + 1]);
  }
};