struct sieve {
  vector<int> primes, prime, sd;
  sieve(int n) : prime(n + 1, true), sd(n + 1, 1) {
    prime[1] = false;
    for (int i = 2; i <= n; i++) {
      if (prime[i]) {
        primes.push_back(i);
        sd[i] = i;
      }
      for (int j = 0; j < (int)primes.size() && i * primes[j] <= n; j++) {
        prime[i * primes[j]] = false;
        sd[i * primes[j]] = primes[j];
        if (i % primes[j] == 0) break;
      }
    }
  }
};