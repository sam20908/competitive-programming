template <typename T, typename A, typename C, typename C2 = C, typename F = identity>
struct segment_tree_persistent {
  struct node_t {
    node_t *l = nullptr, *r = nullptr;
    T v;
  };
  node_t *root0;
  int n;
  A apply;
  C combine;
  C2 query_combine;
  F query_fn;
  segment_tree_persistent(int n, T v, A apply, C combine, C2 query_combine = {}, F query_fn = {}) : n(n), apply(apply), combine(combine), query_combine(query_combine), query_fn(query_fn) {
    auto dfs = [&](auto &self, int tl, int tr) -> node_t * {
      if (tl == tr)
        return new node_t{.v = v};
      int tm = (tl + tr) / 2;
      auto node_l = self(self, tl, tm), node_r = self(self, tm + 1, tr);
      return new node_t{node_l, node_r, combine(node_l->v, node_r->v)};
    };
    root0 = dfs(dfs, 0, n - 1);
  }
  template <typename... Args>
  node_t *update(node_t *root, int i, Args &&...args) {
    auto dfs = [&](auto &self, node_t *cur, int tl, int tr) -> node_t * {
      if (tl == tr) {
        T new_v = cur->v;
        apply(new_v, std::forward<Args>(args)...);
        return new node_t{.v = new_v};
      }
      int tm = (tl + tr) / 2;
      auto node_l = i <= tm ? self(self, cur->l, tl, tm) : cur->l;
      auto node_r = i > tm ? self(self, cur->r, tm + 1, tr) : cur->r;
      return new node_t{node_l, node_r, combine(node_l->v, node_r->v)};
    };
    return dfs(dfs, root, 0, n - 1);
  }
  template <typename R = T, typename... Args>
  R query(node_t *root, int l, int r, R ans = {}, Args &&...args) {
    auto dfs = [&](auto &self, node_t *cur, int tl, int tr, int l, int r) -> R {
      if (l > r)
        return ans;
      if (tl == l && tr == r)
        return query_fn(cur->v, std::forward<Args>(args)...);
      int tm = (tl + tr) / 2;
      return query_combine(self(self, cur->l, tl, tm, l, min(r, tm)), self(self, cur->r, tm + 1, tr, max(l, tm + 1), r));
    };
    return dfs(dfs, root, 0, n - 1, l, r);
  }
};