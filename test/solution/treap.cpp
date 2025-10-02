// https://cses.fi/problemset/model/2072/

#include <chrono>
#include <iostream>
#include <random>
#include <tuple>
using namespace std;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Treap {
  Treap *left = nullptr, *right = nullptr;
  int v, weight, sz = 1;
  Treap() {}
  Treap(int v) : v(v), weight(rng()) {}

  static void update(Treap *node) {
    node->sz = 1;
    if (node->left)
      node->sz += node->left->sz;
    if (node->right)
      node->sz += node->right->sz;
  }

  // Merges the treaps a and b.
  static Treap *merge(Treap *a, Treap *b) {
    if (!a)
      return b;
    if (!b)
      return a;
    Treap *r;
    if (a->weight < b->weight) {
      a->right = merge(a->right, b);
      r = a;
    } else {
      b->left = merge(a, b->left);
      r = b;
    }
    update(r);
    return r;
  }

  // Splits the treap into two treaps.
  // The first of the returned treaps will contain the k first nodes of a.
  static pair<Treap *, Treap *> split(Treap *a, int k) {
    if (!a)
      return {nullptr, nullptr};
    int al = a->left ? a->left->sz : 0;
    Treap *r;
    if (al >= k) {
      tie(r, a->left) = split(a->left, k);
      update(a);
      return {r, a};
    }
    tie(a->right, r) = split(a->right, k - al - 1);
    update(a);
    return {a, r};
  }

  static void print(Treap *a, char endl = '\n') {
    if (a->left)
      print(a->left, '\0');
    cout << (char)a->v;
    if (a->right)
      print(a->right, '\0');
    if (endl)
      cout << endl;
  }
};

Treap *new_treap(int v) {
  const int pool_sz = 2e5;
  static Treap pool[pool_sz];
  static Treap *pool_ptr = pool;

  *pool_ptr = Treap(v);
  return pool_ptr++;
}

int main() {
  Treap *root = nullptr;

  int n, m;
  cin >> n >> m;

  string s;
  cin >> s;

  for (char c : s) {
    root = Treap::merge(root, new_treap(c));
  }

  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    auto [r0, r1] = Treap::split(root, a - 1);
    auto [r2, r3] = Treap::split(r1, b - a + 1);
    root = Treap::merge(r0, r3);
    root = Treap::merge(root, r2);
  }

  Treap::print(root);
}