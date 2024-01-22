#include <bits/stdc++.h>
using namespace std;

struct segment_tree {
  struct node_t {
    int v = 0;
  };
  int n = 0;
  vector<node_t> t;
  segment_tree(int n) : n(n), t(4 * n) {}
  void update(int i, int v) {
    auto f = [&](auto &self, int tl, int tr, int node) -> void {
      if (tl == tr)
        t[node].v += v;
      else {
        int tm = (tl + tr) / 2;
        if (i <= tm)
          self(self, tl, tm, 2 * node);
        else
          self(self, tm + 1, tr, 2 * node + 1);
        auto &a = t[2 * node], &b = t[2 * node + 1];
        t[node].v = a.v + b.v;
      }
    };
    f(f, 0, n - 1, 1);
  }
  auto query(int l, int r) {
    auto f = [&](auto &self, int l, int r, int tl, int tr, int node) {
      if (l > r)
        return 0;
      if (tl == l && tr == r)
        return t[node].v;
      int tm = (tl + tr) / 2;
      auto a = self(self, l, min(r, tm), tl, tm, 2 * node);
      auto b = self(self, max(l, tm + 1), r, tm + 1, tr, 2 * node + 1);
      return a + b;
    };
    return f(f, l, r, 0, n - 1, 1);
  }
};