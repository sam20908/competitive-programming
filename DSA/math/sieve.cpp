#include <bits/stdc++.h>
using namespace std;

struct sieve {
  vector<int> p, pd;
  sieve(int n) : pd(n + 1) {
    iota(pd.begin(), pd.end(), 0);
    for (int i = 2; i <= n; i++) {
      if (pd[i] == i)
        p.push_back(i);
      for (int j = 0; j < (int)p.size() && i * p[j] <= n; j++) {
        pd[i * p[j]] = p[j];
        if (i % p[j] == 0)
          break;
      }
    }
  }
  bool is_prime(int x) { return x > 1 && pd[x] == x; }
};