template <int MOD = 1'000'000'007, typename T = long long> struct mod_int {
  T v{};
  mod_int() = default;
  mod_int(T vx) : v((vx + MOD) % MOD) {}
  mod_int &operator=(T vx) {
    v = (vx + MOD) % MOD;
    return *this;
  }
#define OP(op)                                                                                                         \
  friend mod_int operator op(const mod_int &a, const mod_int &b) { return ((a.v op b.v) % MOD + MOD) % MOD; }          \
  friend mod_int operator op(T a, const mod_int &b) { return (((a % MOD + MOD) % MOD op b.v) % MOD + MOD) % MOD; }     \
  mod_int &operator op##=(const mod_int &other) {                                                                      \
    v = ((v op other.v) % MOD + MOD) % MOD;                                                                            \
    return *this;                                                                                                      \
  }
  OP(+)
  OP(-)
  OP(*)
#undef OP
  friend bool operator==(const mod_int &a, const mod_int &b) { return a.v == b.v; }
  friend bool operator!=(const mod_int &a, const mod_int &b) { return a.v != b.v; }
};