// https://cses.fi/problemset/model/2106/

#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct HashString {
  const ll M = 1111111111111111111; // M is a prime.
  const ll C = uniform_int_distribution<ll>(0.1 * M, 0.9 * M)(rng);

  ll mul(ll a, ll b) { return __int128(a) * b % M; }

  int n;
  vector<ll> pows, sums;

  HashString(string s) : n(s.size()), pows(n + 1, 1), sums(n + 1) {
    for (int i = 1; i <= n; i++) {
      pows[i] = mul(pows[i - 1], C);
      sums[i] = (mul(sums[i - 1], C) + s[i - 1]) % M;
    }
  }

  // Returns the hash of the substring [l, r)
  ll hash(int l, int r) {
    ll h = sums[r] - mul(sums[l], pows[r - l]);
    return (h % M + M) % M;
  }
};

int main() {
  string s;
  cin >> s;
  int n = s.size();
  HashString hs(s);

  auto find = [&](int len) {
    set<ll> hashes;
    for (int i = 0; i <= n - len; i++) {
      ll h = hs.hash(i, i + len);
      if (hashes.count(h))
        return i;
      hashes.insert(h);
    }
    return -1;
  };

  int len = 0;
  int first = 0;
  for (int b = 1 << 16; b >= 1; b /= 2) {
    int pos = find(len + b);
    if (pos == -1)
      continue;
    first = pos;
    len += b;
  }

  if (len == 0) {
    cout << "-1\n";
  } else {
    cout << s.substr(first, len) << "\n";
  }
}