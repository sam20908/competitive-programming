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

vec<uint64_t> VALS;
struct custom_hash {
  static uint64_t getfixed(int i) {
    while (VALS.size() < i + 1)
      if (VALS.empty())
        VALS.push_back(chrono::steady_clock::now().time_since_epoch().count());
      else
        VALS.push_back(splitmix64(VALS.back()));
    return VALS[i];
  }
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const { return splitmix64(x + getfixed(0)); }
  template <typename... Ts> size_t operator()(const tuple<Ts...> t) const {
    int ic = 0;
    uint64_t rh = 0;
    apply(
        [&](auto &&...args) {
          ((rh ^= splitmix64(args + getfixed(ic++))), ...);
        },
        t);
    return rh;
  }
  template <typename T> size_t operator()(const vector<T> v) const {
    uint64_t rh = getfixed(0);
    for (int i = 0; i < v.size(); i++)
      rh ^= splitmix64(v[i] + getfixed(i + 1));
    return rh;
  }
};

template <typename A, typename B> using tensor_map = umap<A, B, custom_hash>;
template <typename A> using tensor_set = uset<A, custom_hash>;
using pii = pair<int, int>;
using pipii = pair<int, pii>;
using ppiipii = pair<pii, pii>;
using pippiipii = pair<int, pair<pii, pii>>;
using ll = long long;

constexpr int dx[] = {-1, 0, 0, 1, -1, -1, 1, 1};
constexpr int dy[] = {0, -1, 1, 0, -1, 1, -1, 1};
constexpr int INF = (int)1e9 + 15;
constexpr ll INFL = ll(1e18) + 15;
constexpr double EPS = 1e-9;
constexpr int P = 31;
constexpr int P2 = 33;
constexpr int M = (int)1e9 + 7;
constexpr int M2 = (int)1e9 + 9;

constexpr int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
constexpr int lcm(int a, int b) { return (a * b) / gcd(a, b); }

struct dsu {
  vec<int> parent, rank;
  int distinct;
  dsu(int n) : parent(n), rank(n, 1), distinct(n) {
    for (int i = 0; i < n; i++)
      parent[i] = i;
  }
  int find(int i) {
    if (parent[i] == i)
      return i;
    return parent[i] = find(parent[i]);
  }
  void unite(int i, int j) {
    if (find(i) != find(j)) {
      distinct--;
      int repi = find(i);
      int repj = find(j);
      if (rank[repi] < rank[repj])
        swap(repi, repj);
      parent[repj] = repi;
      rank[repi] += int(rank[repi] == rank[repj]);
    }
  }
};

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
