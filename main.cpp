#ifdef LC_LOCAL
#include "parser.hpp"
#define dbg(...) CONCAT(DBG_, NUM_ARGS(__VA_ARGS__))(__VA_ARGS__), cout << endl
#else
#define dbg(...)
#endif

#define all(x) begin(x), end(x)
#define has(c, x) (c.find(x) != c.end())
#define umap unordered_map
#define uset unordered_set
#define vec vector
#define valid(i, j, m, n) (i >= 0 && i < m && j >= 0 && j < n)

template <typename T> T &amin(T &a, const T &b) { return a = min(a, b); }
template <typename T> T &amax(T &a, const T &b) { return a = max(a, b); }

using pii = pair<int, int>;
using pipii = pair<int, pii>;
using ppiipii = pair<pii, pii>;
using pippiipii = pair<int, pair<pii, pii>>;
using ll = long long;

constexpr int dx[] = {-1, 0, 0, 1, -1, -1, 1, 1};
constexpr int dy[] = {0, -1, 1, 0, -1, 1, -1, 1};
constexpr int INF = 1e9;
constexpr ll INFL = 1e18;
constexpr double EPS = 1e-9;
constexpr int MOD = 1e9 + 7;

constexpr int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
constexpr int lcm(int a, int b) { return (a * b) / gcd(a, b); }

// ----- CHANGE FOR PROBLEM -----
class Solution {
public:
  void test() {}
};
// ----- CHANGE FOR PROBLEM -----

#ifdef LC_LOCAL
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  exec(&Solution::test); // CHANGE FOR PROBLEM
}
#endif
