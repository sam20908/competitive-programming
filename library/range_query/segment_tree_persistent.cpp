template <typename T>
struct segment_tree_persistent {
  struct node_t {
    node_t *l, *r;
    T v;
  };
  int n;
  function<T(T, T)> combine;
  list<node_t> nodes; // avoid invalidating references by growth from vector
  node_t *new_node(node_t *l, node_t *r, const T &v) {
    return &nodes.emplace_back(node_t{l, r, v});
  }
  segment_tree_persistent(int n, function<T(T, T)> combine) : n(n), combine(std::move(combine)) {
    auto dfs = [&](auto &self, int tl, int tr) -> node_t * {
      if (tl == tr)
        return new_node(nullptr, nullptr, T{});
      int tm = (tl + tr) / 2;
      auto l = self(self, tl, tm);
      auto r = self(self, tm + 1, tr);
      return new_node(l, r, this->combine(l->v, r->v));
    };
    dfs(dfs, 0, n - 1);
  }
  segment_tree_persistent(const vector<T> &v, function<T(T, T)> combine) : n(v.size()), combine(std::move(combine)) {
    auto dfs = [&](auto &self, int tl, int tr) -> node_t * {
      if (tl == tr)
        return new_node(nullptr, nullptr, v[tl]);
      int tm = (tl + tr) / 2;
      auto l = self(self, tl, tm);
      auto r = self(self, tm + 1, tr);
      return new_node(l, r, this->combine(l->v, r->v));
    };
    dfs(dfs, 0, n - 1);
  }
  node_t *update(node_t *root, int i, const T &v) {
    auto dfs = [&](auto &self, node_t *cur, int tl, int tr) -> node_t * {
      if (tl == tr) {
        return new_node(nullptr, nullptr, combine(cur->v, v));
      }
      int tm = (tl + tr) / 2;
      auto l = i <= tm ? self(self, cur->l, tl, tm) : cur->l;
      auto r = i > tm ? self(self, cur->r, tm + 1, tr) : cur->r;
      return new_node(l, r, combine(l->v, r->v));
    };
    return dfs(dfs, root, 0, n - 1);
  }

  node_t *set(node_t *root, int i, const T &v) {
    auto dfs = [&](auto &self, node_t *cur, int tl, int tr) -> node_t * {
      if (tl == tr) {
        return new_node(nullptr, nullptr, v);
      }
      int tm = (tl + tr) / 2;
      auto l = i <= tm ? self(self, cur->l, tl, tm) : cur->l;
      auto r = i > tm ? self(self, cur->r, tm + 1, tr) : cur->r;
      return new_node(l, r, combine(l->v, r->v));
    };
    return dfs(dfs, root, 0, n - 1);
  }
  optional<T> query(node_t *root, int l, int r) {
    auto dfs = [&](auto &self, node_t *cur, int tl, int tr, int ql, int qr) -> optional<T> {
      if (ql > qr)
        return nullopt;
      if (tl == ql && tr == qr)
        return cur->v;
      int tm = (tl + tr) / 2;
      auto ansl = self(self, cur->l, tl, tm, ql, min(qr, tm));
      auto ansr = self(self, cur->r, tm + 1, tr, max(ql, tm + 1), qr);
      return ansl && ansr ? combine(*ansl, *ansr) : ansl ? ansl : ansr;
    };
    return dfs(dfs, root, 0, n - 1, l, r);
  }
};
