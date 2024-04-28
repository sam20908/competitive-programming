#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifndef ONLINE_JUDGE
#define eprintf(...) fprintf(stderr, __VA_ARGS__);
#else
#define eprintf(...)
#endif

#define ALL(x) begin(x), end(x)
#define SUM(x) accumulate(ALL(x), 0LL)

using ll = long long;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {}

int main() {
  ios::sync_with_stdio(false);
#if 1
  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    eprintf("\nTest %d\n", i);
    solve();
  }
#else
  eprintf("\nTest\n");
  solve();
#endif
  eprintf("\n");
}
