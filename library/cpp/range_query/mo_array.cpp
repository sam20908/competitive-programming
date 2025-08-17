template <typename R, typename... Args>
struct mo_array {
  vector<pair<int, int>> q;
  vector<tuple<Args...>> ans_args;
  function<void(int)> add, erase; // FIXME: Use function_ref in C++26
  function<R(Args...)> get_ans;
  mo_array(function<void(int)> add, function<void(int)> erase, function<R(Args...)> get_ans) : add(std::move(add)), erase(std::move(erase)), get_ans(get_ans) {}
  void add_query(int l, int r, const Args &...args) {
    q.push_back({l, r});
    ans_args.emplace_back(args...);
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
    vector<R> ans(n);
    for (int i = 0; i < n; i++) {
      while (cr < q[ord[i]].second)
        add(++cr);
      while (q[ord[i]].first < cl)
        add(--cl);
      while (q[ord[i]].second < cr)
        erase(cr--);
      while (cl < q[ord[i]].first)
        erase(cl++);
      ans[ord[i]] = apply(get_ans, ans_args[ord[i]]);
    }
    return ans;
  }
};