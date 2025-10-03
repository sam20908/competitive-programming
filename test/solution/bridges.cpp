// https://leetcode.com/problems/critical-connections-in-a-network/solutions/7238751/easiest-approach-c-beats-90/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<vector<int>> criticalConnections(int n,
                                          vector<vector<int>> &connections) {
    vector<vector<int>> adj(n);
    int e = connections.size();
    for (int i = 0; i < e; i++) {
      adj[connections[i][0]].push_back(connections[i][1]);
      adj[connections[i][1]].push_back(connections[i][0]);
    }
    int timer = 0;
    vector<int> disc(n, -1);
    vector<int> low(n, -1);
    int par = -1;
    vector<vector<int>> result;
    for (int i = 0; i < n; i++) {
      if (disc[i] == -1) {
        dfs(i, par, disc, low, result, adj, timer);
      }
    }
    return result;
  }
  void dfs(int i, int par, vector<int> &disc, vector<int> &low,
           vector<vector<int>> &result, vector<vector<int>> &adj, int timer) {
    disc[i] = low[i] = timer++;
    for (int nbr : adj[i]) {
      if (nbr == par) {
        continue;
      } else if (disc[nbr] == -1) {
        dfs(nbr, i, disc, low, result, adj, timer);
        low[i] = min(low[i], low[nbr]);
        if (low[nbr] > disc[i]) {
          result.push_back({i, nbr});
        }
      } else {
        low[i] = min(low[i], disc[nbr]);
      }
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> ed;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    ed.push_back({a, b});
  }
  auto ans = Solution().criticalConnections(n, ed);
  cout << ans.size() << '\n';
  for (auto &v : ans) {
    cout << v[0] << ' ' << v[1] << '\n';
  }
}