template <typename T, typename U> T last_true(T lo, T hi, U f) {
  --lo;
  while (lo < hi) {
    T mid = lo + (hi - lo + 1) / 2;
    f(mid) ? lo = mid : hi = mid - 1;
  }
  return lo;
}