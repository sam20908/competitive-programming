// https://cses.fi/problemset/model/1648/
// Fenwick Tree also works here.

#include <iostream>
using namespace std;
using ll = long long;

const int TREE_SIZE = 1 << 18;
ll tree[TREE_SIZE * 2];

void change(int i, int x) {
  i += TREE_SIZE;
  tree[i] = x;
  while (i > 1) {
    i /= 2;
    tree[i] = tree[i * 2] + tree[i * 2 + 1];
  }
}

// Returns the sum of values in range [l, r]
ll get_sum(int l, int r) {
  ll res = 0;
  l += TREE_SIZE;
  r += TREE_SIZE;
  while (l <= r) {
    if (l % 2 == 1)
      res += tree[l++];
    if (r % 2 == 0)
      res += tree[r--];
    l /= 2;
    r /= 2;
  }
  return res;
}

int main() {
  int n, q;
  cin >> n >> q;

  for (int i = 1; i <= n; ++i) {
    int x;
    cin >> x;
    change(i, x);
  }

  for (int qi = 0; qi < q; ++qi) {
    int t;
    cin >> t;
    if (t == 1) {
      int k, u;
      cin >> k >> u;
      change(k, u);
    } else {
      int l, r;
      cin >> l >> r;
      cout << get_sum(l, r) << '\n';
    }
  }
}