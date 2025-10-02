// https://cses.fi/problemset/model/1647/

#include <iostream>
using namespace std;

const int N = 200000;
const int L = 20;

int x[N];
int table[N][L];

// Returns the minimum value in range [l, r)
int get_min(int l, int r) {
  // __lg(x) returns the base-2 logarithm of x, rounded down.
  // With it, we'll figure out the largest power of two
  // that is not larger than the length of the query.
  int i = __lg(r - l);
  return min(table[l][i], table[r - (1 << i)][i]);
}

int main() {
  int n, q;
  cin >> n >> q;

  for (int i = 0; i < n; ++i) {
    cin >> x[i];
    table[i][0] = x[i];
  }

  for (int j = 0; (1 << j) < n; ++j) {
    for (int i = 0; i + (1 << j) < n; ++i) {
      table[i][j + 1] = min(table[i][j], table[i + (1 << j)][j]);
    }
  }

  for (int qi = 0; qi < q; ++qi) {
    int l, r;
    cin >> l >> r;
    l--;
    cout << get_min(l, r) << '\n';
  }
}