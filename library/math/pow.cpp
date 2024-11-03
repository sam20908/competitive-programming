template <typename T>
constexpr T pow(T a, T b, int m, T one = {1}) {
  a %= m;
  T res = one;
  while (b > 0) {
    if (b & 1)
      res = res * a % m;
    a = a * a % m;
    b >>= 1;
  }
  return res;
}