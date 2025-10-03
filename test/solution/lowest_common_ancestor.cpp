// https://cses.fi/problemset/model/1688/

#include <iostream>
#include <vector>
using namespace std;

const int N = 200000;
int jmp[N][20];
int depth[N];
vector<int> g[N];

void dfs(int node) {
  for (int child : g[node]) {
    depth[child] = depth[node] + 1;
    dfs(child);
  }
}

int lca(int a, int b) {
  if (depth[a] < depth[b]) {
    swap(a, b);
  }
  int depth_difference = depth[a] - depth[b];
  for (int j = 19; j >= 0; --j) {
    if ((1 << j) & depth_difference) {
      a = jmp[a][j];
    }
  }
  if (a == b) {
    return a;
  } else {
    for (int j = 19; j >= 0; --j) {
      if (jmp[a][j] != jmp[b][j]) {
        a = jmp[a][j];
        b = jmp[b][j];
      }
    }
    return jmp[a][0];
  }
}

int main() {
  int n, q;

  cin >> n >> q;

  for (int i = 1; i < n; ++i) {
    cin >> jmp[i][0];
    jmp[i][0]--;
    g[jmp[i][0]].push_back(i);
  }

  for (int j = 0; (1 << j) <= n; ++j) {
    for (int i = 0; i < n; ++i) {
      jmp[i][j + 1] = jmp[jmp[i][j]][j];
    }
  }

  dfs(0);

  for (int qi = 0; qi < q; ++qi) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    cout << lca(a, b) + 1 << '\n';
  }
}