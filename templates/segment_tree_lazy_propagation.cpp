struct segment {
  int m = 0;
  vector<long long> tree, lazy;
  segment(int n) : m(n), tree(4 * n), lazy(4 * n) {}
  void update(int l, int r, long long v) {
    auto f = [&](auto &self, int tl, int tr, int n) -> void {
      if (lazy[n] != 0) {
        tree[n] += (tr - tl + 1) * lazy[n];
        if (tl != tr) {
          lazy[2 * n + 1] += lazy[n];
          lazy[2 * n + 2] += lazy[n];
        }
        lazy[n] = 0;
      }
      if (tl > tr || l > tr || r < tl)
        return;
      if (l <= tl && tr <= r) {
        tree[n] += (tr - tl + 1) * v;
        if (tl != tr) {
          lazy[2 * n + 1] += v;
          lazy[2 * n + 2] += v;
        }
      } else {
        int mid = (tl + tr) / 2;
        self(self, tl, mid, 2 * n + 1);
        self(self, mid + 1, tr, 2 * n + 2);
        tree[n] = tree[2 * n + 1] + tree[2 * n + 2];
      }
    };
    f(f, 0, m - 1, 0);
  }
  long long query(int l, int r) {
    auto f = [&](auto &self, int tl, int tr, int n) -> long long {
      if (lazy[n] != 0) {
        tree[n] += (tr - tl + 1) * lazy[n];
        if (tl != tr) {
          lazy[2 * n + 1] += lazy[n];
          lazy[2 * n + 2] += lazy[n];
        }
        lazy[n] = 0;
      }
      if (tl > tr || l > tr || r < tl)
        return 0;
      if (l <= tl && tr <= r) {
        return tree[n];
      } else {
        int mid = (tl + tr) / 2;
        return self(self, tl, mid, 2 * n + 1) + self(self, mid + 1, tr, 2 * n + 2);
      }
    };
    return f(f, 0, m - 1, 0);
  }
};