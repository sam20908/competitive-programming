struct rolling_hash {
  static constexpr uint64_t M = (1ULL << 61) - 1;
  static constexpr int P = 257;
  static constexpr uint64_t mul(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & M) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & M) + (ret >> 61);
    ret = (ret & M) + (ret >> 61);
    return ret - 1;
  }
  inline static vector<uint64_t> p = vector<uint64_t>{1};
  vector<uint64_t> h;
  rolling_hash(int n, string &s) : h(n + 1) {
    for (uint64_t i = p.size(), pp = p.back(); i <= n; i++)
      p.push_back(pp = mul(pp, P));
    for (int i = n - 1; i >= 0; i--)
      h[i] = (s[i] + mul(h[i + 1], P)) % M;
  }
  uint64_t hash(int l, int r) {
    return (h[l] - mul(h[r + 1], p[r - l + 1]) + M) % M;
  }
};