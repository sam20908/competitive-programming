template <int MOD = 1'000'000'007> struct mod_int {
  long long v{};
  mod_int() = default;
  mod_int(long long vx) : v((vx + MOD) % MOD) {}
  mod_int &operator=(long long vx) {
    v = (vx + MOD) % MOD;
    return *this;
  }
#define OP(op)                                                                                                         \
  friend mod_int operator op(const mod_int &a, const mod_int &b) { return (a.v op b.v) % MOD; }                        \
  friend mod_int operator op(long long a, const mod_int &b) { return ((a + MOD) % MOD op b.v) % MOD; }                 \
  friend mod_int operator op(const mod_int &a, long long b) { return (a.v op(b + MOD) % MOD) % MOD; }                  \
  mod_int &operator op##=(const mod_int &other) {                                                                      \
    v = (v op other.v) % MOD;                                                                                          \
    return *this;                                                                                                      \
  }                                                                                                                    \
  mod_int &operator op##=(long long other) {                                                                           \
    v = (v op(other + MOD) % MOD) % MOD;                                                                               \
    return *this;                                                                                                      \
  }
  OP(+)
  OP(-)
  OP(*)
#undef OP
  friend bool operator==(const mod_int &a, const mod_int &b) { return a.v == b.v; }
  friend bool operator!=(const mod_int &a, const mod_int &b) { return a.v != b.v; }
  using conv_t = long long;
  operator conv_t() { return v; }
};