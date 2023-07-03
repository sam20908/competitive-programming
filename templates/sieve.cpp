struct sieve {
  vector<int> primes, composite, sd;
  sieve(int n) : composite(n + 1), sd(n + 1) {
    for (int i = 2; i <= n; i++) {
      if (!composite[i]) primes.push_back(i);
      for (int j = 0; j < primes.size() && i * primes[j] <= n; j++) {
        composite[i * primes[j]] = true;
        if (i % primes[j] == 0) break;
      }
    }
  }
};