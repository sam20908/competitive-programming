#include <bits/stdc++.h>
using namespace std;

struct aho_corasick {
  vector<int> link, next_match;
  vector<vector<int>> next, matches;
  aho_corasick(int n, vector<string> &words) {
    int m = 0;
    for (int i = 0; i < (int)words.size(); i++)
      m += words[i].size();
    link.resize(m + 1);
    next.resize(m + 1, vector<int>(26, -1));
    next_match.resize(m + 1);
    matches.resize(m + 1);
    int new_node = 1;
    for (int i = 0; i < (int)words.size(); i++) {
      int cur = 0;
      for (char c : words[i]) {
        if (next[cur][c - 'a'] == -1)
          next[cur][c - 'a'] = new_node++;
        cur = next[cur][c - 'a'];
      }
      matches[cur].push_back(i);
    }
    queue<int> q;
    for (int a = 0; a < 26; a++)
      if (next[0][a] != -1)
        q.push(next[0][a]);
      else
        next[0][a] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v = 0; v < 26; v++)
        if (next[u][v] != -1) {
          int cur_link = link[u];
          while (next[cur_link][v] == -1)
            cur_link = link[cur_link];
          link[next[u][v]] = next[cur_link][v];
          next_match[next[u][v]] = !matches[link[next[u][v]]].empty()
                                       ? link[next[u][v]]
                                       : next_match[link[next[u][v]]];
          q.push(next[u][v]);
        }
    }
  }
  vector<pair<int, int>> occurences(string &s) {
    vector<pair<int, int>>
        ans; // [occurence ending index, index of word matched]
    int cur = 0;
    for (int i = 0; i < (int)s.size(); i++) {
      while (next[cur][s[i] - 'a'] == -1)
        cur = link[cur];
      cur = next[cur][s[i] - 'a'];
      int cur_occurence = cur;
      while (cur_occurence) {
        for (auto match : matches[cur_occurence])
          ans.push_back({i, match});
        cur_occurence = next_match[cur_occurence];
      }
    }
    return ans;
  }
};