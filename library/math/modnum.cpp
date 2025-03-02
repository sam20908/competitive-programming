/**
 * @brief Wrapper to keep an integer in respect to modulo.
 *
 * @tparam M Modulus.
 * @tparam T Internal value type.
 */
template <int M, typename T = int>
struct modnum {
  T v{};

  constexpr modnum() = default;

  /**
   * @brief Initialize the wrapper to the value (mod M).
   *
   * @param vx Value to initialize to.
   */
  constexpr modnum(long long vx) : v((vx % M + M) % M) {}

  constexpr modnum &operator=(long long vx) {
    v = (vx % M + M) % M;
    return *this;
  }

  /**
   * @brief Computes (v^p) mod M.
   *
   * @param p Exponent to raise.
   * @return Resulting integer in another wrapper.
   */
  constexpr modnum<M, T> pow(long long p) const {
    long long a = v, res = 1;
    for (; p; p >>= 1, a = a * a % M)
      if (p & 1)
        res = res * a % M;
    return res;
  }

  /**
   * @brief Computes the modular inverse of the value (mod M).
   *
   * @return Modular inverse.
   */
  constexpr modnum<M, T> inv() const {
    return pow(M - 2);
  }

  constexpr explicit operator T() const {
    return v;
  }

  constexpr modnum<M, T> operator%(long long mod) const {
    return v % mod;
  }

#define OP(op)                                                            \
  constexpr friend modnum operator op(const modnum &a, const modnum &b) { \
    return ((1LL * a.v op b.v) % M + M) % M;                              \
  }                                                                       \
  constexpr modnum &operator op##=(const modnum & other) {                \
    v = ((1LL * v op other.v) % M + M) % M;                               \
    return *this;                                                         \
  }
  OP(+)
  OP(-)
  OP(*)
#undef OP
};