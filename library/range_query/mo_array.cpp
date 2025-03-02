/**
 * @brief Run Mo's Algorithm to answer subarray queries offline.
 *
 * @param q List of queries
 * @param heuristic Returns an list of comparable objects dictating the order the queries will be answered.
 * @param add Adds the current element. Called as `fn(index)`.
 * @param remove Removes the current element. Called as `fn(index)`.
 * @param answer Returns the current answer.
 * @return List of answers in the corresponding index of the queries.
 */
auto mo_array(vector<pair<int, int>> &q, auto &&heuristic, auto &&add, auto &&remove, auto &&answer) {
  int m = q.size();
  auto h = heuristic(q);
  vector<int> ord(m);
  iota(ord.begin(), ord.end(), 0);
  ranges::sort(ord, [&](int i, int j) {
    return h[i] < h[j];
  });
  int cl = 0, cr = -1;
  vector<decay_t<decltype(answer())>> ans(m);
  for (int i = 0; i < m; i++) {
    while (cr < q[ord[i]].second)
      add(++cr);
    while (q[ord[i]].first < cl)
      add(--cl);
    while (q[ord[i]].second < cr)
      remove(cr--);
    while (cl < q[ord[i]].first)
      remove(cl++);
    ans[ord[i]] = answer();
  }
  return ans;
}