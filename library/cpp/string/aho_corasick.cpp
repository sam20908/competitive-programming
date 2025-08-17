template <int Begin, int End>
struct aho_corasick {
  struct node_t {
    int g[End - Begin + 1]{};
    int link = 0, exit = 0;
    vector<int> matches;
  };
  vector<node_t> t = vector<node_t>(1);
  aho_corasick(const vector<string> &w) {
    for (int i = 0; i < (int)w.size(); i++) {
      int u = 0;
      for (char c : w[i]) {
        if (!t[u].g[c - Begin]) {
          t[u].g[c - Begin] = t.size();
          t.push_back({});
        }
        u = t[u].g[c - Begin];
      }
      t[u].matches.push_back(i);
    }
    queue<int> q{{0}};
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int a = 0; a <= End - Begin; a++) {
        if (int v = t[u].g[a]) {
          t[v].link = u ? t[t[u].link].g[a] : 0;
          t[v].exit = t[t[v].link].matches.empty() ? t[t[v].link].exit : t[v].link;
          q.push(v);
        } else
          t[u].g[a] = t[t[u].link].g[a];
      }
    }
  }
};
