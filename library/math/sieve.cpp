/**
 * @brief Precomputes the primes as well as the smallest prime divisor of all numbers [1,`n`].
 */
struct sieve {
  vector<int> primes, spd;

  /**
   * @brief Precomputes the information up to `n`.
   *
   * @param n Bound of the precomputation.
   */
  sieve(int n) : spd(n + 1) {
    iota(spd.begin(), spd.end(), 0);
    for (int i = 2; i <= n; i++) {
      if (spd[i] == i)
        primes.push_back(i);
      for (int j = 0; j < (int)primes.size() && i * primes[j] <= n; j++) {
        spd[i * primes[j]] = primes[j];
        if (i % primes[j] == 0)
          break;
      }
    }
  }

  /**
   * @brief Check whether the given integer is a prime.
   *
   * @param x Value to check.
   * @return Whether it is a prime.
   */
  bool is_prime(int x) {
    return x > 1 && spd[x] == x;
  }

  /**
   * @brief Compute the list of divisors of the given integer.
   *
   * @param x Value to get the divisors of.
   * @return List of divisors.
   */
  vector<int> divisors(int x) {
    vector<int> ans;
    while (x > 1)
      for (int d = spd[x], sd = spd[x], n = ans.size(); spd[x] == sd; d *= sd, x /= sd) {
        for (int i = 0; i < n; i++)
          ans.push_back(d * ans[i]);
        ans.push_back(d);
      }
    return ans;
  }
};