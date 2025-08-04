template <int M>
struct modnum {
  int v{};
  constexpr modnum() = default;
  constexpr modnum(long long vx) : v((vx % M + M) % M) {}
  constexpr modnum &operator=(long long vx) {
    v = (vx % M + M) % M;
    return *this;
  }
  constexpr modnum pow(long long p) const {
    long long a = v, res = 1;
    for (; p; p >>= 1, a = a * a % M)
      if (p & 1)
        res = res * a % M;
    return res;
  }
  constexpr modnum inv() const {
    return pow(M - 2);
  }
  constexpr explicit operator long long() const {
    return v;
  }
#define OP(op, op2, f)                                                    \
  constexpr modnum &operator op##=(const modnum & other) {                \
    v = ((1LL * v op2 other.f) % M + M) % M;                              \
    return *this;                                                         \
  }                                                                       \
  constexpr friend modnum operator op(const modnum &a, const modnum &b) { \
    auto c = a;                                                           \
    c op## = b;                                                           \
    return c;                                                             \
  }
  OP(+, +, v)
  OP(-, -, v)
  OP(*, *, v)
  OP(/, *, inv().v)
#undef OP
};