/*

number of shortest paths, Dijkstra, DP

Introduction to Algorithms (Fall 2018)
Quiz 2.5 - Shortest Paths
https://oj.nctu.edu.tw/problems/758/

*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::fill;
using std::greater;
using std::ios_base;
using std::priority_queue;
using std::vector;

struct V {
  int i, d;

  bool operator > (const V &v) const {
    return this->d > v.d;
  }
};

struct E {
  int v, w;
  E *n;
};

priority_queue<V, vector<V>, greater<V>> q;
int n, m, u, v, w, i, d[10000], p[10000], s[10000];
E *e[10000], *t;
V b, c;

void add(int u, int v, int w) {
  t = new E;
  t->v = v;
  t->w = w;
  t->n = e[u];
  e[u] = t;
  t = new E;
  t->v = u;
  t->w = w;
  t->n = e[v];
  e[v] = t;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); 
  cin >> n >> m;
  for (i = 0; i != m; ++i) {
    cin >> u >> v >> w;
    add(u, v, w);
  }
  fill(d + 1, d + n, 2147483647);
  p[0] = 1;
  b.i = 0;
  b.d = 0;
  q.push(b);
  while (!q.empty()) {
    c = q.top();
    q.pop();
    if (c.i == n - 1)
      break;
    if (s[c.i])
      continue;
    s[c.i] = 1;
    t = e[c.i];
    while (t != NULL) {
      if (d[c.i] + t->w < d[t->v]) {
        d[t->v] = d[c.i] + t->w;
        p[t->v] = p[c.i];
        b.i = t->v;
        b.d = d[t->v];
        q.push(b);
      } else if (d[c.i] + t->w == d[t->v]) {
        p[t->v] += p[c.i];
        p[t->v] %= 524287;
      }
      t = t->n;
    }
  }
  cout << p[n - 1];
}
