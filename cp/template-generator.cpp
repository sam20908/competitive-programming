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
#define REP(i, n) for (int i = 0; i < n; i++)
#define PER(i, n) for (int i = n - 1; i >= 0; i--)

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;

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
