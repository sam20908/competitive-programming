struct trie {
  struct node {
    vec<node *> adj = vec<node *>(26, nullptr);
    bool end = false;
  };
  node *root = new node();
  void insert(string &s) {
    auto cur = root;
    for (int i = 0; i < s.size(); i++) {
      auto &next = cur->adj[s[i] - 'a'];
      if (!next)
        next = new node();
      cur = next;
    }
    cur->end = true;
  }
  bool search(string &s) {
    auto cur = root;
    for (int i = 0; i < s.size(); i++) {
      auto &next = cur->adj[s[i] - 'a'];
      if (!next)
        return false;
      cur = next;
    }
    return cur->end;
  }
};