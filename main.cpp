#ifdef LC_LOCAL
#include "parser.hpp"
#define dbg(...) CONCAT(DBG_, NUM_ARGS(__VA_ARGS__))(__VA_ARGS__), cout << endl
#else
#define dbg(...)
template <typename T, typename = void> struct is_container {
  static constexpr bool value = false;
};
template <typename T>
struct is_container<T, void_t<decltype(T{}.begin()), decltype(T{}.end())>> {
  static constexpr bool value = true;
};
#endif
template <typename T, typename = void> struct is_tuple_like {
  static constexpr bool value = false;
};
template <typename T>
struct is_tuple_like<T, void_t<typename tuple_size<T>::type>> {
  static constexpr bool value = true;
};

#define all(x) begin(x), end(x)
#define has(c, x) (c.find(x) != c.end())
#define vec vector
#define umap unordered_map
#define uset unordered_set
#define valid(i, j, m, n) (i >= 0 && i < m && j >= 0 && j < n)

template <typename T> T &amin(T &a, const T &b) { return a = min(a, b); }
template <typename T> T &amax(T &a, const T &b) { return a = max(a, b); }

vec<size_t> VALS;
struct custom_hash {
  static size_t getfixed(int i) {
    while (VALS.size() < i + 1)
      if (VALS.empty())
        VALS.push_back(chrono::steady_clock::now().time_since_epoch().count());
      else
        VALS.push_back(splitmix64(VALS.back()));
    return VALS[i];
  }
  static size_t splitmix64(size_t x) {
    x += (size_t)0x9e3779b97f4a7c15;
    x = (x ^ (x >> (size_t)30)) * (size_t)0xbf58476d1ce4e5b9;
    x = (x ^ (x >> (size_t)27)) * (size_t)0x94d049bb133111eb;
    return x ^ (x >> (size_t)31);
  }
  size_t operator()(size_t x) const { return splitmix64(x + getfixed(0)); }
  template <typename T>
  enable_if_t<is_tuple_like<T>::value, size_t> operator()(const T &t) const {
    int ic = 0;
    size_t rh = 0;
    apply(
        [&](auto &&...args) {
          ((rh ^= splitmix64(args + getfixed(ic++))), ...);
        },
        t);
    return rh;
  }
  template <typename T>
  enable_if_t<is_container<T>::value, size_t> operator()(const T &t) const {
    size_t rh = getfixed(0);
    for (int i = 0; i < t.size(); i++)
      rh ^= splitmix64(t[i] + getfixed(i));
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
