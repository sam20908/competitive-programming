struct fenwick {
  int n;
  vec<int> BIT;
  fenwick(int n) : n(n + 1), BIT(n + 2) {}
  void update(int i, int v) {
    for (; i <= n; i += (i & (-i)))
      BIT[i] += v;
  }
  int prefix_sum(int i) {
    int sum = 0;
    for (; i > 0; i -= (i & (-i)))
      sum += BIT[i];
    return sum;
  }
};