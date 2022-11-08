#ifdef LC_LOCAL
#include "parser.hpp"
#else
#define dbg(...)
#endif

#define all(x) x.begin(), x.end()
#define has(c, x) (c.find(x) != c.end())
#define valid(i, j, m, n) (i >= 0 && i < m && j >= 0 && j < n)

template <typename T> T &amin(T &a, const T &b) { return a = min(a, b); }
template <typename T> T &amax(T &a, const T &b) { return a = max(a, b); }
template <typename T> using v = vector<T>;
template <typename T> using vv = vector<v<T>>;
template <typename T> using vvv = vector<vv<T>>;
template <typename T> using vvvv = vector<vvv<T>>;

constexpr int dx[] = {-1, 0, 0, 1, -1, -1, 1, 1};
constexpr int dy[] = {0, -1, 1, 0, -1, 1, -1, 1};
constexpr int MXN = (int)1e6;
constexpr int INF = (int)1e9 + 15;
constexpr long long INFL = (long long)1e18 + 15;
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