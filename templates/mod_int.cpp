template <int MOD = 1'000'000'007> struct mod_int {
  long long v{};
  mod_int() = default;
  mod_int(long long vx) : v((vx + MOD) % MOD) {}
  mod_int &operator=(long long vx) {
    v = (vx + MOD) % MOD;
    return *this;
  }
  friend mod_int operator+(const mod_int &a, const mod_int &b) { return (a.v + b.v) % MOD; }
  friend mod_int operator+(long long a, const mod_int &b) { return ((a + MOD) % MOD + b.v) % MOD; }
  friend mod_int operator+(const mod_int &a, long long b) { return (a.v + (b + MOD) % MOD) % MOD; }
  friend mod_int operator-(const mod_int &a, const mod_int &b) { return (a.v - b.v + MOD) % MOD; }
  friend mod_int operator-(long long a, const mod_int &b) { return ((a + MOD) % MOD - b.v + MOD) % MOD; }
  friend mod_int operator-(const mod_int &a, long long b) { return (a.v - (b + MOD) % MOD + MOD) % MOD; }
  friend mod_int operator*(const mod_int &a, const mod_int &b) { return (a.v * b.v) % MOD; }
  friend mod_int operator*(long long a, const mod_int &b) { return (((a + MOD) % MOD) * b.v) % MOD; }
  friend mod_int operator*(const mod_int &a, long long b) { return (a.v * ((b + MOD) % MOD)) % MOD; }
  friend bool operator==(const mod_int &a, const mod_int &b) { return a.v == b.v; }
  friend bool operator!=(const mod_int &a, const mod_int &b) { return a.v != b.v; }
};