/**
 * @brief Convenient precomputation wrapper to get the hash of any substring with the same degree hash.
 *        Typical implementations use pairs of hashes, while this one uses a sufficient big modulus for 64-bit hash.
 */
class rolling_hash {
  static constexpr uint64_t M = (1ULL << 61) - 1, P = 257;
  inline static vector<uint64_t> p = vector<uint64_t>{1};
  vector<uint64_t> h;

public:
  /**
   * @brief Precomputes the rolling hash for the given string.
   *
   * @param s String to precompute the rolling hash for.
   */
  rolling_hash(const string &s) {
    int n = s.size();
    h.resize(n + 1);
    for (uint64_t i = p.size(), pp = p.back(); i <= n; i++)
      p.push_back(pp = __uint128_t(pp) * P % M);
    for (int i = n - 1; i >= 0; i--)
      h[i] = (s[i] + __uint128_t(h[i + 1]) * P % M) % M;
  }

  /**
   * @brief Get the hash of substring s[l..r].
   *
   * @param l Left boundary inclusive.
   * @param r Right boundary inclusive.
   * @return 64-bit hash.
   */
  uint64_t hash(int l, int r) const {
    return (h[l] - __uint128_t(h[r + 1]) * p[r - l + 1] % M + M) % M;
  }
};