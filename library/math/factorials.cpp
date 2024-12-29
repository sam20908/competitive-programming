template <int M, typename T = int>
struct factorials {
  vector<T> fact, ifact, inv;
  factorials(int n) : fact(n + 1, 1), ifact(n + 1, 1), inv(n + 1, 1) {
    for (int i = 2; i <= n; i++) {
      fact[i] = 1LL * fact[i - 1] * i % M;
      inv[i] = 1LL * (M - M / i) * inv[M % i] % M;
      ifact[i] = 1LL * ifact[i - 1] * inv[i] % M;
    }
  }
  T ncr(int n, int k) const {
    return 1LL * fact[n] * ifact[k] % M * ifact[n - k] % M;
  }
  T npr(int n, int k) const {
    return 1LL * fact[n] * ifact[n - k] % M;
  }
};