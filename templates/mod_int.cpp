struct mod_int {
  long long v{};
  mod_int() = default;
  mod_int(long long vx) : v((vx % M + M) % M) {}
  friend mod_int operator+(const mod_int &a, const mod_int &b) { return {(a.v + b.v) % M}; }
  friend mod_int operator+(long long a, const mod_int &b) { return {(a + b.v) % M}; }
  friend mod_int operator+(const mod_int &a, long long b) { return {(a.v + b) % M}; }
  friend mod_int operator-(const mod_int &a, const mod_int &b) { return {(a.v - b.v + M) % M}; }
  friend mod_int operator-(long long a, const mod_int &b) { return {(a - b.v + M) % M}; }
  friend mod_int operator-(const mod_int &a, long long b) { return {(a.v - b + M) % M}; }
  friend mod_int operator*(const mod_int &a, const mod_int &b) { return {(a.v * b.v) % M}; }
  friend mod_int operator*(long long a, const mod_int &b) { return {(a * b.v) % M}; }
  friend mod_int operator*(const mod_int &a, long long b) { return {(a.v * b) % M}; }
  friend bool operator==(const mod_int &a, const mod_int &b) { return a.v == b.v; }
  friend bool operator!=(const mod_int &a, const mod_int &b) { return a.v != b.v; }
};