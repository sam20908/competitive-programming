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

#define all(x) begin(x), end(x)

using ll = long long;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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