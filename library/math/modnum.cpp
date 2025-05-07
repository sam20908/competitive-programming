template <int M>
struct modnum {
  inline static consteval bool mod_is_prime() {
    int l = 0, r = M;
    while (r - l > 1) {
      int m = (l + r) >> 1;
      if (1ll * m * m <= M)
        l = m;
      else
        r = m;
    }
    for (int i = 2; i <= l; i++)
      if (M % i == 0)
        return false;
    return M != 1;
  }
  static_assert(mod_is_prime(), "modulus has to be prime");
  long long v{};
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
  struct combinatorics {
    vector<modnum> fact, ifact, inv;
    combinatorics(int n) : fact(n + 1, 1), ifact(n + 1, 1), inv(n + 1, 1) {
      for (int i = 2; i <= n; i++) {
        fact[i] = 1LL * fact[i - 1] * i;
        inv[i] = 1LL * (M - M / i) * inv[M % i];
        ifact[i] = 1LL * ifact[i - 1] * inv[i];
      }
    }
    modnum ncr(int n, int k) const {
      return fact[n] * ifact[k] * ifact[n - k];
    }
    modnum npr(int n, int k) const {
      return fact[n] * ifact[n - k];
    }
  };
};