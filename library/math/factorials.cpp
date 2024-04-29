template <int M>
struct factorials {
  vector<long long> fact, ifact, inv;
  factorials(int n) : fact(n + 1, 1), ifact(n + 1, 1), inv(n + 1, 1) {
    for (int i = 2; i <= n; i++) {
      fact[i] = fact[i - 1] * i % M;
      inv[i] = 1LL * (M - M / i) * inv[M % i] % M;
      ifact[i] = ifact[i - 1] * inv[i] % M;
    }
  }
  long long ncr(int n, int k) {
    return fact[n] * ifact[k] % M * ifact[n - k] % M;
  }
  long long npr(int n, int k) {
    return fact[n] * ifact[n - k] % M;
  }
};