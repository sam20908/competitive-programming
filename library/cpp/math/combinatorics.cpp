template <int M>
struct combinatorics {
  vector<modnum<M>> fact, ifact, inv;
  combinatorics(int n) : fact(n + 1, 1), ifact(n + 1, 1), inv(n + 1, 1) {
    for (int i = 2; i <= n; i++) {
      fact[i] = 1LL * fact[i - 1] * i;
      inv[i] = 1LL * (M - M / i) * inv[M % i];
      ifact[i] = 1LL * ifact[i - 1] * inv[i];
    }
  }
  modnum<M> ncr(int n, int k) const {
    return fact[n] * ifact[k] * ifact[n - k];
  }
  modnum<M> npr(int n, int k) const {
    return fact[n] * ifact[n - k];
  }
};