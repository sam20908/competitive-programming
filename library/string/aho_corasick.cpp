struct aho_corasick {
  struct node_t {
    int g[26]{};
    int link = 0, mlink = 0, match = -1;
    node_t() {
      ranges::fill(g, -1);
    }
  };
  vector<node_t> v = vector<node_t>(1);
  template <invocable<int, int> F>
  aho_corasick(const vector<string> &w, F f) {
    for (int i = 0; i < (int)w.size(); i++) {
      int u = 0;
      for (char c : w[i]) {
        if (v[u].g[c - 'a'] == -1) {
          v[u].g[c - 'a'] = v.size();
          v.push_back({});
        }
        u = v[u].g[c - 'a'];
      }
      v[u].match = i;
      f(i, u);
    }
    queue<int> q;
    for (int a = 0; a < 26; a++)
      if (v[0].g[a] != -1)
        q.push(v[0].g[a]);
      else
        v[0].g[a] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int a = 0; a < 26; a++)
        if (v[u].g[a] != -1) {
          int l = v[u].link;
          while (v[l].g[a] == -1)
            l = v[l].link;
          v[v[u].g[a]].link = v[l].g[a];
          v[v[u].g[a]].mlink = v[v[l].g[a]].match == -1 ? v[v[l].g[a]].mlink : v[l].g[a];
          q.push(v[u].g[a]);
        }
    }
  }
  template <invocable<int, int, int> F>
    requires requires(F f) {
      { f(0, 0, 0) } -> std::convertible_to<bool>;
    }
  void iterate(const string &s, F f) {
    for (int i = 0, u = 0; i < (int)s.size(); i++) {
      while (v[u].g[s[i] - 'a'] == -1)
        u = v[u].link;
      u = v[u].g[s[i] - 'a'];
      for (int p = v[u].match == -1 ? v[u].mlink : u && f(i, v[p].match, p); p; p = v[p].mlink) {
      }
    }
    {}
  }
};