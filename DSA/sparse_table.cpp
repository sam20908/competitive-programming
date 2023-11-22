struct sparse_table {
  vector<vector<int>> dp;
  int k = 0;
  sparse_table(vector<int> &v): k(__lg(v.size())) {
    int n = v.size();
    dp.resize(k + 1, vector<int>(n));
    ranges::copy(v, dp[0].begin());
    for (int i = 1; i <= k; i++)
      for (int j = 0; j + (1 << i) <= n; j++) {
        auto a = dp[i - 1][j];
        auto b = dp[i - 1][j + (1 << (i - 1))];
        dp[i][j] = min(a, b);
      }
  }
  int query(int l, int r) {
    int ans = 2e9;
    for (int i = k; i >= 0; i--) {
      if ((1 << i) <= r - l + 1) {
        auto a = ans;
        auto b = dp[i][l];
        ans = min(a, b);
        l += 1 << i;
      }
    }
    return ans;
  }
  int query_fast(int l, int r) { // only use if operation is idempotent!
    int i = __lg(r - l + 1);
    auto a = dp[i][l];
    auto b = dp[i][r - (1 << i) + 1];
    return min(a, b);
  }
};