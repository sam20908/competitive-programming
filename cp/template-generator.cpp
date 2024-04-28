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

void gen() {}

int main() {
  ios::sync_with_stdio(false);

  ll seed;
  scanf("%lld", &seed);
  srand(seed);

#if 1
  printf("1\n");
#endif

  gen();
}
