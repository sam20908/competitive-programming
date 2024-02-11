#include <bits/stdc++.h>
using namespace std;

struct sieve {
  vector<int> p, spd;
  sieve(int n) : spd(n + 1) {
    iota(spd.begin(), spd.end(), 0);
    for (int i = 2; i <= n; i++) {
      if (spd[i] == i)
        p.push_back(i);
      for (int j = 0; j < (int)p.size() && i * p[j] <= n; j++) {
        spd[i * p[j]] = p[j];
        if (i % p[j] == 0)
          break;
      }
    }
  }
  bool is_prime(int x) { return x > 1 && spd[x] == x; }
};