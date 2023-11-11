struct sieve {
  vector<int> primes, prime_divisor;
  sieve(int n): prime_divisor(n + 1) {
    iota(prime_divisor.begin(), prime_divisor.end(), 0);
    for (int i = 2; i <= n; i++) {
      if (prime_divisor[i] == i) primes.push_back(i);
      for (int j = 0; j < (int)primes.size() && i * primes[j] <= n; j++) {
        prime_divisor[i * primes[j]] = primes[j];
        if (i % primes[j] == 0) break;
      }
    }
  }
  bool is_prime(int x) {
    return x > 1 && prime_divisor[x] == x;
  }
};