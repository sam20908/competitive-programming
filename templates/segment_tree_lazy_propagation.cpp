struct segment {
  vec<ll> tree, lazy;
  segment(int n) : tree(4 * n), lazy(4 * n) {}
  void update(int l, int r, int tl, int tr, int n, ll v) {
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
      update(l, r, tl, mid, 2 * n + 1, v);
      update(l, r, mid + 1, tr, 2 * n + 2, v);
      tree[n] = tree[2 * n + 1] + tree[2 * n + 2];
    }
  }
  ll query(int l, int r, int tl, int tr, int n) {
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
      return query(l, r, tl, mid, 2 * n + 1) + query(l, r, mid + 1, tr, 2 * n + 2);
    }
  }
};