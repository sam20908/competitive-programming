template <typename T> struct BIT {
  vector<T> bit; // one-indexed
  int m;
  BIT(int n): bit(n + 1), m(n + 1) {}
  T query(int i) {
    T ans = 0;
    for (; i > 0; i -= i & -i) ans += bit[i];
    return ans;
  }
  void update(int i, T delta) {
    for (; i < m; i += i & -i) bit[i] += delta;
  }
};
