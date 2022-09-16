constexpr int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
constexpr int lcm(int a, int b) { return (a * b) / gcd(a, b); }

constexpr ll binpow(ll a, ll b, ll m) {
  a %= m;
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      res = res * a % m;
    a = a * a % m;
    b >>= 1;
  }
  return res;
}