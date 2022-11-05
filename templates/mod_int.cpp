struct mint {
  ll v{};
  mint(ll vx) : v((vx % M + M) % M) {}
  friend mint operator+(const mint &a, const mint &b) { return {(a.v + b.v) % M}; }
  friend mint operator+(ll a, const mint &b) { return {(a + b.v) % M}; }
  friend mint operator+(const mint &a, ll b) { return {(a.v + b) % M}; }
  friend mint operator*(const mint &a, const mint &b) { return {(a.v * b.v) % M}; }
  friend mint operator*(ll a, const mint &b) { return {(a * b.v) % M}; }
  friend mint operator*(const mint &a, ll b) { return {(a.v * b) % M}; }
  friend bool operator==(const mint &a, const mint &b) { return a.v != b.v; }
  friend bool operator<(const mint &a, const mint &b) { return a.v < b.v; }
  friend bool operator>(const mint &a, const mint &b) { return a.v > b.v; }
  mint &operator+=(const mint &a) {
    v = (v + a.v) % M;
    return *this;
  }
};