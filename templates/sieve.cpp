struct sieve {
  vector<int> primes, composite, sd;
  sieve(int n) : composite(n + 1), sd(n + 1) {
    sd[1] = 1;
    for (int i = 2; i <= n; i++) {
      if (!composite[i]) {
        primes.push_back(i);
        sd[i] = i;
      }
      for (int j = 0; j < primes.size() && i * primes[j] <= n; j++) {
        composite[i * primes[j]] = true;
        sd[i * primes[j]] = primes[j];
        if (i % primes[j] == 0) break;
      }
    }
  }
};