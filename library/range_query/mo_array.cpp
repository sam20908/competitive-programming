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
  auto solve() {
    int n = q.size();
    auto hilbert = q | views::transform([](auto p) {
                     int x = p.first, y = p.second;
                     const uint64_t l = __lg(max(x, y) * 2 + 1) | 1;
                     const uint64_t mx = (1ull << l) - 1;
                     uint64_t ans = 0;
                     for (uint64_t s = 1ull << (l - 1); s; s >>= 1) {
                       bool rx = x & s, ry = y & s;
                       ans = (ans << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
                       if (!rx) {
                         if (ry)
                           x ^= mx, y ^= mx;
                         swap(x, y);
                       }
                     }
                     return ans;
                   }) |
        ranges::to<vector>();
    auto ord = views::iota(0, n) | ranges::to<vector>();
    ranges::sort(ord, {}, [&](int i) {
      return hilbert[i];
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