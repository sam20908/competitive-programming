// https://leetcode.com/problems/number-of-zigzag-arrays-ii/solutions/7229933/matrix-exponentiation-intuition-from-q3-video-included-codeforces-blog/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// Codeforces Matrix Expo template (Errichto)
struct Matrix {
  vector<vector<int>> m;
  int sz;
  Matrix(int n, bool ident = false) : sz(n) {
    m.assign(n, vector<int>(n, 0));
    if (ident) {
      for (int i = 0; i < n; ++i)
        m[i][i] = 1;
    }
  }
  Matrix operator*(const Matrix &o) const {
    Matrix res(sz);
    for (int i = 0; i < sz; ++i) {
      for (int k = 0; k < sz; ++k) {
        if (!m[i][k])
          continue;
        long long val = m[i][k];
        for (int j = 0; j < sz; ++j) {
          res.m[i][j] = (res.m[i][j] + val * o.m[k][j]) % MOD;
        }
      }
    }
    return res;
  }
};

Matrix mpow(Matrix base, long long exp) {
  Matrix res(base.sz, true);
  while (exp > 0) {
    if (exp & 1)
      res = res * base;
    base = base * base;
    exp >>= 1;
  }
  return res;
}

class Solution {
public:
  int zigZagArrays(long long n, int l, int r) {

    auto now = make_tuple(n, l, r);

    int m = r - l + 1; // number of distinct values
    int S = 2 * m;     // total states (value, direction)

    auto id = [&](int val, int dir) { return (val - l) * 2 + dir; };

    // Build adjacency matrix
    Matrix A(S);

    for (int val = l; val <= r; ++val) {
      for (int dir = 0; dir < 2; ++dir) {
        int u = id(val, dir);
        if (dir == 0) {
          // last was decreasing => next must be greater
          for (int nxt = val + 1; nxt <= r; ++nxt) {
            int v = id(nxt, 1);
            A.m[u][v] = 1;
          }
        } else {
          // last was increasing => next must be smaller
          for (int nxt = l; nxt < val; ++nxt) {
            int v = id(nxt, 0);
            A.m[u][v] = 1;
          }
        }
      }
    }

    vector<int> V0(S, 1);
    if (n == 1) {
      long long ans = 0;
      for (int x : V0)
        ans = (ans + x) % MOD;
      return ans;
    }

    Matrix An = mpow(A, n - 1);

    vector<long long> V(S, 0);
    for (int j = 0; j < S; ++j) {
      long long sum = 0;
      for (int i = 0; i < S; ++i) {
        sum += 1LL * V0[i] * An.m[i][j];
        if (sum >= 8LL * MOD)
          sum %= MOD;
      }
      V[j] = sum % MOD;
    }

    long long ans = 0;
    for (auto x : V)
      ans = (ans + x) % MOD;
    return ans;
  }
};

int main() {
  int n, l, r;
  cin >> n >> l >> r;
  cout << Solution().zigZagArrays(n, l, r) << '\n';
}