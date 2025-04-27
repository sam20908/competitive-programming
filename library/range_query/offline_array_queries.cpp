template <typename F>
struct offline_array_queries {
  vector<pair<int, int>> q;
  function<void(int)> add, erase; // FIXME: Use function_ref in C++26
  F get_ans;
  offline_array_queries(function<void(int)> add, function<void(int)> erase, F get_ans) : add(std::move(add)), erase(std::move(erase)), get_ans(get_ans) {}
  void add_query(int l, int r) {
    q.push_back({l, r});
  };
  auto solve(auto &&heuristic) {
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
        erase(cr--);
      while (cl < q[ord[i]].first)
        erase(cl++);
      ans[ord[i]] = get_ans();
    }
    return ans;
  }
};