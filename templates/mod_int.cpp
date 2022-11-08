struct mint {
  long long v{};
  mint() = default;
  mint(long long vx) : v((vx % M + M) % M) {}
  friend mint operator+(const mint &a, const mint &b) { return {(a.v + b.v) % M}; }
  friend mint operator+(long long a, const mint &b) { return {(a + b.v) % M}; }
  friend mint operator+(const mint &a, long long b) { return {(a.v + b) % M}; }
  friend mint operator*(const mint &a, const mint &b) { return {(a.v * b.v) % M}; }
  friend mint operator*(long long a, const mint &b) { return {(a * b.v) % M}; }
  friend mint operator*(const mint &a, long long b) { return {(a.v * b) % M}; }
  friend bool operator==(const mint &a, const mint &b) { return a.v != b.v; }
  friend bool operator<(const mint &a, const mint &b) { return a.v < b.v; }
  friend bool operator>(const mint &a, const mint &b) { return a.v > b.v; }
  mint &operator+=(const mint &a) {
    v = (v + a.v) % M;
    return *this;
  }
};