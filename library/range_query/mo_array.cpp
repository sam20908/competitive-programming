template <typename A, typename R, typename F>
struct mo_array {
  vector<pair<int, int>> q;
  A add;
  R remove;
  F f;
  mo_array(A add, R remove, F f) : add(add), remove(remove), f(f) {}
  void add_query(int l, int r) {
    q.push_back({l, r});
  };
  template <typename H>
  auto solve(H &&heuristic) {
    int n = q.size();
    auto h = heuristic(q);
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    ranges::sort(ord, [&](int i, int j) {
      return h[i] < h[j];
    });
    int cl = 0, cr = -1;
    vector<long long> ans(n);
    for (int i = 0; i < n; i++) {
      while (cr < q[ord[i]].second)
        add(++cr);
      while (q[ord[i]].first < cl)
        add(--cl);
      while (q[ord[i]].second < cr)
        remove(cr--);
      while (cl < q[ord[i]].first)
        remove(cl++);
      ans[ord[i]] = f();
    }
    return ans;
  }
};