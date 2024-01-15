#include <bits/stdc++.h>
using namespace std;

struct segment {
  struct node_t {
    int v = 0;
  };
  int n = 0;
  vector<node_t> t, p;
  segment(int n): n(n), t(4 * n), p(4 * n) {}
  void propagate(int tl, int tr, int node) {
    t[node].v += p[node].v * (tr - tl + 1);
    if (tl != tr) {
      p[2 * node].v += p[node].v;
      p[2 * node + 1].v += p[node].v;
    }
    p[node].v = 0;
  }
  void update(int l, int r, int v) {
    auto f = [&](auto &self, int l, int r, int tl, int tr, int node) -> void {
      propagate(tl, tr, node);
      if (l <= r) {
        if (tl == l && tr == r) {
          p[node].v += v;
          propagate(tl, tr, node);
        } else {
          int tm = (tl + tr) / 2;
          self(self, l, min(r, tm), tl, tm, 2 * node);
          self(self, max(l, tm + 1), r, tm + 1, tr, 2 * node + 1);
          auto &a = t[2 * node], &b = t[2 * node + 1];
          t[node].v = a.v + b.v;
        }
      }
    };
    f(f, l, r, 0, n - 1, 1);
  }
  auto query(int l, int r) {
    auto f = [&](auto &self, int l, int r, int tl, int tr, int node) {
      propagate(tl, tr, node);
      if (l > r) return 0;
      if (tl == l && tr == r) return t[node].v;
      int tm = (tl + tr) / 2;
      auto a = self(self, l, min(r, tm), tl, tm, 2 * node);
      auto b = self(self, max(l, tm + 1), r, tm + 1, tr, 2 * node + 1);
      return a + b;
    };
    return f(f, l, r, 0, n - 1, 1);
  }
};