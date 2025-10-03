// https://cses.fi/problemset/model/2104/
// I know this isn't Aho-Corasick but correct implementation also solves it.

#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct SuffixAutomaton {
  struct State {
    int len;
    State *link;
    map<char, State *> next;
    bool final;
    int pos;
  };

  State *first, *last;

  SuffixAutomaton(string s) {
    first = last = new State{};
    for (auto c : s) {
      auto *add = new State{};
      add->len = last->len + 1;
      add->link = first;
      State *cur = last;
      while (cur && !cur->next[c]) {
        cur->next[c] = add;
        cur = cur->link;
      }
      if (cur && cur->next[c] != add) {
        State *mid = cur->next[c];
        if (cur->len + 1 == mid->len) {
          add->link = mid;
        } else {
          auto *copy = new State(*mid);
          copy->len = cur->len + 1;
          add->link = mid->link = copy;
          while (cur && cur->next[c] == mid) {
            cur->next[c] = copy;
            cur = cur->link;
          }
        }
      }
      last = add;
    }
    State *cur = last;
    while (cur->len) {
      cur->final = true;
      cur = cur->link;
    }
    last->pos = s.size();
    dfs(first);
  }

  void dfs(State *cur) {
    if (cur->pos)
      return;
    cur->pos = last->pos;
    for (auto [c, p] : cur->next) {
      dfs(p);
      cur->pos = min(cur->pos, p->pos - 1);
    }
  }

  int pos(string p) {
    State *cur = first;
    for (auto c : p) {
      if (!cur->next[c])
        return -1;
      cur = cur->next[c];
    }
    return cur->pos - p.size();
  }
};

int main() {
  string s;
  cin >> s;
  SuffixAutomaton sa(s);

  int k;
  cin >> k;
  for (int ki = 1; ki <= k; ki++) {
    string p;
    cin >> p;
    int pos = sa.pos(p);
    cout << (pos != -1 ? pos + 1 : -1) << "\n";
  }
}