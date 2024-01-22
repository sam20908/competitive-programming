template <int M> struct int_mod {
  long long v{};
  constexpr int_mod() = default;
  constexpr int_mod(long long vx) : v((vx % M + M) % M) {}
  constexpr int_mod &operator=(long long vx) {
    v = (vx % M + M) % M;
    return *this;
  }
#define OP(op)                                                                 \
  constexpr friend int_mod operator op(const int_mod &a, const int_mod &b) {   \
    return ((a.v op b.v) % M + M) % M;                                         \
  }                                                                            \
  constexpr friend int_mod operator op(long long a, const int_mod &b) {        \
    return (((a % M + M) % M op b.v) % M + M) % M;                             \
  }                                                                            \
  constexpr int_mod &operator op##=(const int_mod &other) {                    \
    v = ((v op other.v) % M + M) % M;                                          \
    return *this;                                                              \
  }
  OP(+)
  OP(-)
  OP(*)
#undef OP
  constexpr friend bool operator==(const int_mod &a, const int_mod &b) {
    return a.v == b.v;
  }
  constexpr friend bool operator!=(const int_mod &a, const int_mod &b) {
    return a.v != b.v;
  }
};