// https://codeforces.com/contest/86/submission/175816188

#include <bits/stdc++.h>
using namespace std;
const int B = 400;
long long now, ans[200001], cnt[1000001];
int l, r, n, m, i, a[200001];
struct node {
  int l, r, p;
  int operator<(node u) {
    return l / B == u.l / B ? l / B & 1 ? r < u.r : u.r < r : l < u.l;
  }
} q[200001];
void add(int x, int y) {
  now -= cnt[x] * cnt[x] * x;
  cnt[x] += y;
  now += cnt[x] * cnt[x] * x;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  for (i = 1; i <= n; i++)
    cin >> a[i];
  for (i = 1; i <= m; i++)
    cin >> q[i].l >> q[i].r, q[i].p = i;
  sort(q + 1, q + m + 1);
  l = 1;
  r = 0;
  for (i = 1; i <= m; i++) {
    while (l > q[i].l)
      add(a[--l], 1);
    while (r < q[i].r)
      add(a[++r], 1);
    while (l < q[i].l)
      add(a[l++], -1);
    while (r > q[i].r)
      add(a[r--], -1);
    ans[q[i].p] = now;
  }
  for (i = 1; i <= m; i++)
    cout << ans[i] << "\n";
}