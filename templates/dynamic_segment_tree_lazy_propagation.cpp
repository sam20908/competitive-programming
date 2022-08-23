struct segment {
  struct node {
    node *left = nullptr;
    node *right = nullptr;
    ll val = 0, lazy = 0;
    void extend() {
      if (!left)
        left = new node();
      if (!right)
        right = new node();
    }
  };
  node *root = new node();
  void update(int l, int r, int tl, int tr, ll v, node *cur) {
    if (cur->lazy != 0) {
      cur->val += (tr - tl + 1) * cur->lazy;
      if (tl != tr) {
        cur->extend();
        cur->left->lazy += cur->lazy;
        cur->right->lazy += cur->lazy;
      }
      cur->lazy = 0;
    }
    if (tl > tr || tl > r || tr < l)
      return;
    if (tl >= l && tr <= r) {
      cur->val += (tr - t + 1) * v;
      if (tl != tr) {
        cur->extend();
        cur->left->lazy += v;
        cur->right->lazy += v;
      }
    } else {
      int mid = (tl + tr) / 2;
      cur->extend();
      update(l, r, tl, mid, v, cur->left);
      update(l, r, mid + 1, tr, v, cur->right);
      cur->val = cur->left->val + cur->right->val;
    }
  }
  ll query(int l, int r, int tl, int tr, node *cur) {
    if (cur->lazy != 0) {
      cur->val += (tr - tl + 1) * cur->lazy;
      if (tl != tr) {
        cur->extend();
        cur->left->lazy += cur->lazy;
        cur->right->lazy += cur->lazy;
      }
      cur->lazy = 0;
    }
    if (tl > tr || tl > r || tr < l)
      return 0;
    if (tl >= l && tr <= r) {
      return cur->val;
    } else {
      int mid = (tl + tr) / 2;
      cur->extend();
      return query(l, r, tl, mid, cur->left) +
             query(l, r, mid + 1, tr, cur->right);
    }
  }
};