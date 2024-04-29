#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifdef LC_LOCAL
#include "parser.hpp"
#else
#define dbg(...)
#endif

#define ALL(x) begin(x), end(x)
#define SUM(x) accumulate(ALL(x), 0LL)
#define REP(i, n) for (int i = 0; i < n; i++)
#define PER(i, n) for (int i = n - 1; i >= 0; i--)

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;

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