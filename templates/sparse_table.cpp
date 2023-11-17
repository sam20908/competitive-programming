template <typename T> struct sparse_table {
  vector<vector<T>> dp;
  int k = 0;
  sparse_table(vector<T> v): k(__lg(v.size())) {
    int n = v.size();
    dp.resize(k + 1, vector<T>(n));
    ranges::copy(v, dp[0].begin());
    for (int i = 1; i <= k; i++)
      for (int j = 0; j + (1 << i) <= n; j++) dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
  }
  T query(int l, int r) {
    T ans = 2e9;
    for (int i = k; i >= 0; i--) {
      if ((1 << i) <= r - l + 1) {
        ans = min(ans, dp[i][l]);
        l += 1 << i;
      }
    }
    return ans;
  }
  T query_O1(int l, int r) { // only use if operation is idempotent!
    int i = __lg(r - l + 1);
    return min(dp[i][l], dp[i][r - (1 << i) + 1]);
  }
};