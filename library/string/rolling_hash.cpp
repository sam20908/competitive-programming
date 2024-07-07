// #define ROLLING_HASH_ENABLE_BASE // need fast exponentiation pow()
struct rolling_hash {
  static constexpr int M1 = 1e9 + 7, M2 = 1e9 + 9, P1 = 257, P2 = 261;
  vector<int> h1, h2;
  struct precompute {
    vector<int> p1, p2, i1, i2;
    void expand(int n) {
      auto f = [&](vector<int> &pv, vector<int> &iv, int m, int p) {
        for (long long i = pv.size(), pp = pv.back(); i < n; i++) {
          pv.push_back(pp = (pp * p) % m);
#ifdef ROLLING_HASH_ENABLE_BASE
          iv.push_back(pow(pp, m - 2, m));
#endif
        }
      };
      f(p1, i1, M1, P1);
      f(p2, i2, M2, P2);
    }
  };
  static inline auto pre = precompute{{1}, {1}, {1}, {1}};
  struct proxy_t {
    int l = 0, r = 0;
    rolling_hash *ptr = nullptr;
    int hash1() const {
      return (ptr->h1[r + 1] - ptr->h1[l] + M1) % M1;
    }
    int hash2() const {
      return (ptr->h2[r + 1] - ptr->h2[l] + M2) % M2;
    }
    long long combined() const {
      return 1LL * hash1() * M2 + hash2();
    };
#ifdef ROLLING_HASH_ENABLE_BASE
    int hash1_base() const {
      return 1LL * (ptr->h1[r + 1] - ptr->h1[l] + M1) % M1 * pre.i1[l] % M1;
    }
    int hash2_base() const {
      return 1LL * (ptr->h2[r + 1] - ptr->h2[l] + M2) % M2 * pre.i2[l] % M2;
    }
    long long combined_base() const {
      return 1LL * hash1_base() * M2 + hash2_base();
    };
#endif
    friend bool operator==(const proxy_t &a, const proxy_t &b) {
      long long a1 = a.hash1(), a2 = a.hash2();
      long long b1 = b.hash1(), b2 = b.hash2();
      if (b.l > a.l) {
        a1 = a1 * pre.p1[b.l - a.l] % M1;
        a2 = a2 * pre.p2[b.l - a.l] % M2;
      } else if (a.l > b.l) {
        b1 = b1 * pre.p1[a.l - b.l] % M1;
        b2 = b2 * pre.p2[a.l - b.l] % M2;
      }
      return a1 == b1 && a2 == b2;
    }
  };
  rolling_hash(int n, string &s) : h1(n + 1), h2(n + 1) {
    pre.expand(n);
    auto f = [&](vector<int> &h, vector<int> &pv, int m, int p) {
      for (long long i = 0; i < n; i++) {
        h[i + 1] = (h[i] + 1LL * s[i] * pv[i]) % m;
      }
    };
    f(h1, pre.p1, M1, P1);
    f(h2, pre.p2, M2, P2);
  }
  proxy_t hash(int l, int r) {
    return {l, r, this};
  }
};