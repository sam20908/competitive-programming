template <typename T>
class treap {
public:
  struct node {
    T v, ans;
    int p = rand(), size{1};
    bool rev;
    node *l, *r;
  } *root = nullptr;

private:
  function<T(T, T)> combine;

  int size(node *nd) const {
    return nd ? nd->size : 0;
  }
  void push(node *root) {
    if (root && root->rev) {
      root->rev = false;
      swap(root->l, root->r);
      if (root->l)
        root->l->rev ^= true;
      if (root->r)
        root->r->rev ^= true;
    }
    update(root);
  }
  void update(node *root) {
    if (root) {
      root->size = size(root->l) + size(root->r) + 1;
      root->ans = root->l && root->r ? combine(root->l->ans, root->r->ans) : root->l ? root->l->ans : root->r ? root->r->ans : T{};
      root->ans = combine(root->ans, root->v);
    }
  }

public:
  treap(function<T(T, T)> combine) : combine(std::move(combine)) {}
  treap(const vector<T> &v, function<T(T, T)> cb) : combine(std::move(cb)) {
    int n = v.size();
    auto heapify = [&](auto &&self, node *root) -> void {
      if (!root)
        return;
      auto mx = root;
      if (root->l && root->l->p > mx->p)
        mx = root->l;
      if (root->r && root->r->p > mx->p)
        mx = root->r;
      if (mx != root) {
        swap(root->p, mx->p);
        self(self, mx);
      }
    };
    auto build = [&](auto &&self, int l, int r) -> node * {
      if (l == r)
        return nullptr;
      int m = (l + r) / 2;
      auto root = new node{v[m]};
      root->l = self(self, l, m);
      root->r = self(self, m + 1, r);
      heapify(heapify, root);
      update(root);
      return root;
    };
    root = build(build, 0, n);
  }
  treap(int n, const T &v, function<T(T, T)> combine) : treap(vector<T>(n, v), std::move(combine)) {}

  void split(node *root, int v, node *&l, node *&r) {
    if (!root) {
      l = r = nullptr;
      return;
    }
    push(root);
    if (size(root->l) < v) {
      split(root->r, v - size(root->l) - 1, root->r, r);
      l = root;
    } else {
      split(root->l, v, l, root->l);
      r = root;
    }
    update(root);
  }
  void merge(node *&root, node *l, node *r) {
    push(l);
    push(r);
    if (!l || !r)
      root = l ? l : r;
    else if (l->p > r->p) {
      merge(l->r, l->r, r);
      root = l;
    } else {
      merge(r->l, l, r->l);
      root = r;
    }
    update(root);
  }
  void reverse(node *root, int l, int r) {
    node *tl, *tm, *tr;
    split(root, l, tl, tm);
    split(tm, r - l + 1, tm, tr);
    tm->rev ^= true;
    merge(root, tl, tm);
    merge(root, root, tr);
  }
  optional<T> query(node *root, int l, int r) {
    node *tl, *tm, *tr;
    split(root, l, tl, tm);
    split(tm, r - l + 1, tm, tr);
    auto ans = tm ? optional{tm->ans} : nullopt;
    merge(root, tl, tm);
    merge(root, root, tr);
    return ans;
  }
  vector<T> data(node *root) {
    vector<T> ans;
    auto dfs = [&](auto &&self, node *root) -> void {
      if (!root)
        return;
      push(root);
      self(self, root->l);
      ans.push_back(root->v);
      self(self, root->r);
    };
    dfs(dfs, root);
    return ans;
  }
};
