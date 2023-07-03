constexpr int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}
constexpr int lcm(int a, int b) { return (a * b) / gcd(a, b); }

constexpr long long binpow(long long a, long long b, long long m) {
  a %= m;
  long long res = 1;
  while (b > 0) {
    if (b & 1) res = res * a % m;
    a = a * a % m;
    b >>= 1;
  }
  return res;
}

constexpr int extended_gcd(int a, int b, int &x, int &y) {
  x = 1, y = 0;
  int x1 = 0, y1 = 1, a1 = a, b1 = b;
  while (b1) {
    int q = a1 / b1;
    tie(x, x1) = make_tuple(x1, x - q * x1);
    tie(y, y1) = make_tuple(y1, y - q * y1);
    tie(a1, b1) = make_tuple(b1, a1 - q * b1);
  }
  return a1;
}

template <typename T> constexpr T ceil_div(T a, T b) {
  T res = a / b;
  if (b * res != a) res += (a > 0) & (b > 0);
  return res;
}

const int SIEVE_MAX = 70;
vector<int> prime(SIEVE_MAX + 1, -1);
void sieve() {
  prime[0] = prime[1] = 0;
  for (int i = 2; i <= SIEVE_MAX; i++) {
    if (prime[i] != -1) continue;
    for (int j = i; j <= SIEVE_MAX; j += i) prime[j] = false;
    prime[i] = true;
  }
}
