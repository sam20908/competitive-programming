template <typename T>
vector<vector<T>> rot90(const vector<vector<T>> &v) {
  int n = v.size(), m = v[0].size();
  vector ans(m, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      ans[j][i] = v[i][j];
  ranges::reverse(ans);
  return ans;
}