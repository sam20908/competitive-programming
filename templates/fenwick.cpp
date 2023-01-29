struct fenwick {
  vector<long long> bit; // APIs expect one-indexed index, gives finer control
  int n;
  fenwick(int n) : bit(n + 1), n{n + 1} {}
  long long prefix_sum(int i) {
    long long ans = 0;
    for (; i > 0; i -= i & -i)
      ans += bit[i];
    return ans;
  }
  void add(int i, long long delta) {
    for (; i < n; i += i & -i)
      bit[i] += delta;
  }
};