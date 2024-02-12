#include <bits/stdc++.h>
using namespace std;

struct rolling_hash {
  static constexpr int M1 = 1e9 + 7, M2 = 1e9 + 9, P1 = 31, P2 = 37;
  vector<long long> h1, h2, p1, p2;
  struct hash_pair {
    int l = 0, r = 0;
    rolling_hash *ptr = nullptr;
    friend bool operator==(const hash_pair &a, const hash_pair &b) {
      long long ah1 = (a.ptr->h1[a.r + 1] - a.ptr->h1[a.l] + M1) % M1;
      long long ah2 = (a.ptr->h2[a.r + 1] - a.ptr->h2[a.l] + M2) % M2;
      long long bh1 = (b.ptr->h1[b.r + 1] - b.ptr->h1[b.l] + M1) % M1;
      long long bh2 = (b.ptr->h2[b.r + 1] - b.ptr->h2[b.l] + M2) % M2;
      if (b.l > a.l) {
        ah1 = (ah1 * b.ptr->p1[b.l - a.l]) % M1;
        ah2 = (ah2 * b.ptr->p2[b.l - a.l]) % M2;
      } else if (a.l > b.l) {
        bh1 = (bh1 * a.ptr->p1[a.l - b.l]) % M1;
        bh2 = (bh2 * a.ptr->p2[a.l - b.l]) % M2;
      }
      return ah1 == bh1 && ah2 == bh2;
    }
  };
  rolling_hash(int n, string &s) : h1(n + 1), h2(n + 1), p1(n), p2(n) {
    auto f = [&](vector<long long> &h, vector<long long> &pv, int m, int p) {
      for (long long i = 0, pp = 1; i < n; i++, pp = (pp * p) % m) {
        h[i + 1] = (h[i] + (s[i] - 'a' + 1) * pp) % m;
        pv[i] = pp;
      }
    };
    f(h1, p1, M1, P1);
    f(h2, p2, M2, P2);
  }
  hash_pair hash(int l, int r) { return {l, r, this}; }
};