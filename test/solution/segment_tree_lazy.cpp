#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// This lazy segment tree implementation supports the following operations:
//  1. add(l, r, x): in range [l, r), add x + 0 to the first element,
//                                        x + 1 to the second,
//                                        x + 2 to the third and so on
//  3. query(l, r): find the sum of values in range [l, r)
struct Tree {
  int n;
  vector<ll> sum;
  vector<ll> lazy_a;
  vector<ll> lazy_d;

  Tree(int n) : n(n), sum(n * 4), lazy_a(n * 4), lazy_d(n * 4) {}

  void add(int s, int l, int r, int ql, int qr, int x) {
    if (r <= ql || qr <= l)
      return;
    if (ql <= l && r <= qr) {
      apply(s, r - l, x + (l - ql), 1);
      return;
    }
    push(s, r - l);
    int m = (l + r) / 2;
    add(s * 2 + 0, l, m, ql, qr, x);
    add(s * 2 + 1, m, r, ql, qr, x);
    sum[s] = sum[s * 2] + sum[s * 2 + 1];
  }

  ll query(int s, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l)
      return 0;
    if (ql <= l && r <= qr)
      return sum[s];
    push(s, r - l);
    int m = (l + r) / 2;
    return query(s * 2, l, m, ql, qr) + query(s * 2 + 1, m, r, ql, qr);
  }

  void push(int s, int len) {
    apply(s * 2 + 0, len / 2, lazy_a[s], lazy_d[s]);
    apply(s * 2 + 1, (len + 1) / 2, lazy_a[s] + len / 2 * lazy_d[s], lazy_d[s]);
    lazy_a[s] = 0;
    lazy_d[s] = 0;
  }

  void apply(int s, int len, ll a, ll d) {
    sum[s] += a * len + d * ll(len - 1) * len / 2;
    lazy_a[s] += a;
    lazy_d[s] += d;
  }

  void add(int l, int r, int x) { add(1, 0, n, l, r, x); }
  ll query(int l, int r) { return query(1, 0, n, l, r); }
};

int main() {
  int n, q;
  cin >> n >> q;

  Tree tree(n);

  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    tree.add(i, i + 1, t);
  }

  for (int qi = 0; qi < q; ++qi) {
    int t, l, r;
    cin >> t >> l >> r;
    l--;
    if (t == 1) {
      tree.add(l, r, 1);
    } else {
      cout << tree.query(l, r) << '\n';
    }
  }
}