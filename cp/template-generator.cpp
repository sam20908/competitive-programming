#include <bits/stdc++.h>
using namespace std;

static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void gen() {}

int main() {
  ios::sync_with_stdio(false);
  long long seed;
  scanf("%lld", &seed);
  srand(seed);
  gen();
}
