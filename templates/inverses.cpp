template <int MOD = 1'000'000'007, typename T = long long> struct inverses {
  vector<T> fact, inv, ifact;
  inverses(int n) : fact(n + 1), inv(n + 1), ifact(n + 1) {
    fact[0] = fact[1] = inv[1] = ifact[0] = ifact[1] = 1;
    for (int i = 2; i <= n; i++) {
      fact[i] = fact[i - 1] * i % MOD;
      inv[i] = 1LL * (MOD - MOD / i) * inv[MOD % i] % MOD;
      ifact[i] = ifact[i - 1] * inv[i] % MOD;
    }
  }
  T ncr(int n, int k) { return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD; }
};
