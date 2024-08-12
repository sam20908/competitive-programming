struct rolling_hash {
  static constexpr uint64_t M = (1ULL << 61) - 1, P = 257;
  inline static vector<uint64_t> p = vector<uint64_t>{1};
  vector<uint64_t> h;
  rolling_hash(const string &s) {
    int n = s.size();
    h.resize(n + 1);
    for (uint64_t i = p.size(), pp = p.back(); i <= n; i++)
      p.push_back(pp = __uint128_t(pp) * P % M);
    for (int i = n - 1; i >= 0; i--)
      h[i] = (s[i] + __uint128_t(h[i + 1]) * P % M) % M;
  }
  uint64_t hash(int l, int r) {
    return (h[l] - __uint128_t(h[r + 1]) * p[r - l + 1] % M + M) % M;
  }
};