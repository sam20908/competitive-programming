template <typename T> struct segment {
  static T expand(int l, int r, T v) { return (r - l + 1) * v; }
  static T combine(T a, T b) { return a + b; }
  struct node {
    node *left = nullptr;
    node *right = nullptr;
    T val = T(), lazy = T();
    void extend() {
      if (!left)
        left = new node();
      if (!right)
        right = new node();
    }
    void pushdown(int l, int r, T v) {
      val = combine(expand(l, r, v), val);
      if (l != r) {
        extend();
        left->lazy = combine(left->lazy, v);
        right->lazy = combine(right->lazy, v);
      }
      lazy = T();
    }
  };
  node *root = new node();
  long long m = 0;
  segment(long long n) : m(n) {}
  void update(long long l, long long r, T v) {
    auto f = [&](auto &self, long long tl, long long tr, node *cur) -> void {
      cur->pushdown(tl, tr, cur->lazy);
      if (tl > tr || tl > r || tr < l)
        return;
      if (tl >= l && tr <= r) {
        cur->pushdown(tl, tr, v);
      } else {
        long long mid = tl + (tr - tl) / 2;
        cur->extend();
        self(self, tl, mid, cur->left);
        self(self, mid + 1, tr, cur->right);
        cur->val = combine(cur->left->val, cur->right->val);
      }
    };
    f(f, 0, m - 1, root);
  }
  T query(long long l, long long r) {
    auto f = [&](auto &self, long long tl, long long tr, node *cur) -> T {
      cur->pushdown(tl, tr, cur->lazy);
      if (tl > tr || tl > r || tr < l)
        return T();
      if (tl >= l && tr <= r) {
        return cur->val;
      } else {
        long long mid = tl + (tr - tl) / 2;
        cur->extend();
        return combine(self(self, tl, mid, cur->left), self(self, mid + 1, tr, cur->right));
      }
    };
    return f(f, 0, m - 1, root);
  }
};