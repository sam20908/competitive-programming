/**
 * @brief Computes the factorials as well as their modular inverses up to `n`.
 *
 * @tparam M Modulus.
 * @tparam T Internal value type.
 */
template <int M, typename T = int>
struct factorials {
  vector<T> fact, ifact, inv;

  /**
   * @brief Precompute the factorials and their related information up to `n`.
   *
   * @param n Bound of the computation.
   */
  factorials(int n) : fact(n + 1, 1), ifact(n + 1, 1), inv(n + 1, 1) {
    for (int i = 2; i <= n; i++) {
      fact[i] = 1LL * fact[i - 1] * i % M;
      inv[i] = 1LL * (M - M / i) * inv[M % i] % M;
      ifact[i] = 1LL * ifact[i - 1] * inv[i] % M;
    }
  }

  /**
   * @brief Computes the nCr of the given arguments.
   *
   * @param n
   * @param k
   * @return The nCr.
   */
  T ncr(int n, int k) const {
    return 1LL * fact[n] * ifact[k] % M * ifact[n - k] % M;
  }

  /**
   * @brief Computes the nPr of the given arguments.
   *
   * @param n
   * @param k
   * @return The nPr.
   */
  T npr(int n, int k) const {
    return 1LL * fact[n] * ifact[n - k] % M;
  }
};