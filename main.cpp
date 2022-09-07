#ifdef LC_LOCAL
#include "parser.hpp"
#define dbg(...) CONCAT(DBG_, NUM_ARGS(__VA_ARGS__))(__VA_ARGS__), cout << endl
#else
#define dbg(...)
#endif

#define all(x) begin(x), end(x)
#define has(c, x) (c.find(x) != c.end())
#define vec vector
#define umap unordered_map
#define uset unordered_set
#define valid(i, j, m, n) (i >= 0 && i < m && j >= 0 && j < n)

template <typename T> T &amin(T &a, const T &b) { return a = min(a, b); }
template <typename T> T &amax(T &a, const T &b) { return a = max(a, b); }

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vec<int>;
using vvi = vec<vec<int>>;
using vs = vec<string>;
using vvs = vec<vec<string>>;
using vpii = vec<pii>;

constexpr int dx[] = {-1, 0, 0, 1, -1, -1, 1, 1};
constexpr int dy[] = {0, -1, 1, 0, -1, 1, -1, 1};
constexpr int MXN = (int)1e6;
constexpr int INF = (int)1e9 + 15;
constexpr ll INFL = ll(1e18) + 15;
constexpr double EPS = 1e-9;
constexpr int P = 31;
constexpr int P2 = 33;
constexpr int M = (int)1e9 + 7;
constexpr int M2 = (int)1e9 + 9;

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