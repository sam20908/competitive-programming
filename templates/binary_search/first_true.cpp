template <typename T, typename U> T first_true(T lo, T hi, U f) {
  ++hi;
  while (lo < hi) {
    T mid = lo + (hi - lo) / 2;
    f(mid) ? hi = mid : lo = mid + 1;
  }
  return lo;
}