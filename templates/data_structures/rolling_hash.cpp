#include <bits/stdc++.h>
using namespace std;

struct rolling_hash {
  static constexpr int M1 = 1e9 + 7, M2 = 1e9 + 9, P1 = 257, P2 = 261;
  vector<int> h1, h2;
  struct precompute {
    vector<int> p1, p2;
    void expand(int n) {
      auto f = [&](vector<int> &pv, int m, int p) {
        for (long long i = pv.size(), pp = pv.back(); i < n; i++)
          pv.push_back(pp = (pp * p) % m);
      };
      f(p1, M1, P1);
      f(p2, M2, P2);
    }
  };
  static inline auto pre = precompute{{1}, {1}};
  struct hash_pair {
    int l = 0, r = 0;
    rolling_hash *ptr = nullptr;
    pair<int, int> value() const {
      return {(ptr->h1[r + 1] - ptr->h1[l] + M1) % M1,
              (ptr->h2[r + 1] - ptr->h2[l] + M2) % M2};
    };
    friend bool operator==(const hash_pair &a, const hash_pair &b) {
      auto [ah1, ah2] = a.value();
      auto [bh1, bh2] = b.value();
      if (b.l > a.l) {
        ah1 = 1LL * ah1 * pre.p1[b.l - a.l] % M1;
        ah2 = 1LL * ah2 * pre.p2[b.l - a.l] % M2;
      } else if (a.l > b.l) {
        bh1 = 1LL * bh1 * pre.p1[a.l - b.l] % M1;
        bh2 = 1LL * bh2 * pre.p2[a.l - b.l] % M2;
      }
      return ah1 == bh1 && ah2 == bh2;
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
  hash_pair hash(int l, int r) { return {l, r, this}; }
};