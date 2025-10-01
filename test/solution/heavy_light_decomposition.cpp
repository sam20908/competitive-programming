// ----- CSES ANALYSIS SOLUTION -----

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// This segment tree supports the following operations:
// 1. SegmentTree(v) constructs the tree from the vector v.
// 2. set(k, x) sets the value in position k to x.
// 3. query(l, r) returns the maximum value in range [l, r].
struct SegmentTree {
  int n;
  vector<int> tree;

  SegmentTree(vector<int> &v) {
    n = 1;
    while (n < v.size())
      n *= 2;
    tree.resize(n * 2);
    for (int i = 0; i < v.size(); ++i) {
      tree[i + n] = v[i];
    }
    for (int i = n - 1; i > 0; --i) {
      tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
    }
  }

  void set(int k, int x) {
    k += n;
    tree[k] = x;
    while (k > 1) {
      k /= 2;
      tree[k] = max(tree[k * 2], tree[k * 2 + 1]);
    }
  }

  int query(int l, int r) {
    int ans = 0;
    for (l += n, r += n; l <= r; l /= 2, r /= 2) {
      if (l % 2 == 1)
        ans = max(ans, tree[l++]);
      if (r % 2 == 0)
        ans = max(ans, tree[r--]);
    }
    return ans;
  }
};

using graph = vector<vector<int>>;

// Heavy-light decomposition.
// Decomposes the given tree into heavy and light paths.
// Provides the following functions:
// 1. `position(x)`: Returns the position of node x in the DFS order array.
// 2. `subtree(x)`: Returns range in the DFS order array that corresponds to the
//                  subtree of node x.
// 3. `path_query(a, b, f)`: Partitions the path between nodes a and b into
//                           O(log n) contiguous ranges of the DFS order array.
//                           Calls f(l, r) for each such range [l, r].
//                           The function f may, for example, query/update a
//                           segment tree.
struct HLD {
  int n;
  graph &g;
  vector<int> parent;
  vector<int> jump;
  vector<int> total;
  vector<int> order;

  HLD(graph &g) : n(g.size()), g(g), parent(n), jump(n), total(n), order(n) {
    dfs_size(0);
    int order_index = 0;
    dfs_hld(0, order_index);
  }

  template <typename F> void path_query(int a, int b, F f) {
    for (;; a = parent[jump[a]]) {
      if (order[a] < order[b])
        swap(a, b);
      if (order[jump[a]] <= order[b]) {
        f(order[b], order[a]);
        return;
      }
      f(order[jump[a]], order[a]);
    }
  }

  int position(int x) { return order[x]; }
  pair<int, int> subtree(int x) { return {order[x], order[x] + total[x] - 1}; }

private:
  void dfs_size(int node) {
    total[node] = 1;
    for (auto &child : g[node]) {
      g[child].erase(find(g[child].begin(), g[child].end(), node));
      dfs_size(child);
      total[node] += total[child];
      if (total[child] > total[g[node][0]]) {
        swap(child, g[node][0]);
      }
    }
  }

  void dfs_hld(int node, int &order_index) {
    order[node] = order_index++;
    for (auto child : g[node]) {
      parent[child] = node;
      if (child == g[node][0]) {
        jump[child] = jump[node];
      } else {
        jump[child] = child;
      }
      dfs_hld(child, order_index);
    }
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }

  graph g(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  HLD hld(g);

  vector<int> initial(n);
  for (int i = 0; i < n; ++i) {
    initial[hld.position(i)] = v[i];
  }
  SegmentTree tree(initial);

  for (int qi = 0; qi < q; ++qi) {
    int t;
    cin >> t;
    if (t == 1) {
      int s, x;
      cin >> s >> x;
      tree.set(hld.position(s - 1), x);
    } else {
      int a, b;
      cin >> a >> b;
      int ans = 0;
      auto update_ans = [&](int l, int r) { ans = max(ans, tree.query(l, r)); };
      hld.path_query(a - 1, b - 1, update_ans);
      cout << ans << '\n';
    }
  }
}