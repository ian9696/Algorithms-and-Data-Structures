/*

max min edge of path, disjoint set

Introduction to Algorithms (Fall 2018)
Assignment 18 - Widest Path (0 points, for practice only)
https://oj.nctu.edu.tw/problems/726/

*/

#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::ios_base;
using std::sort;

struct edge {
  int u, v, w;
};

int n, m, i, p[10000];
edge e[1000000];

int cmp(edge a, edge b) {
  return b.w < a.w;
}

int f(int x) {
  return p[x] == x ? x : p[x] = f(p[x]);
}

void u(int x, int y) {
  p[f(x)] = p[f(y)];
}

int c(int x, int y) {
  return f(x) == f(y);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); 
  cin >> n >> m;
  for (i = 0; i != n; ++i)
    p[i] = i;
  for (i = 0; i != m; ++i)
    cin >> e[i].u >> e[i].v >> e[i].w;
  sort(e, e + m, cmp);
  for (i = 0; i != m; ++i) {
    u(e[i].u, e[i].v);
    if (c(0, n - 1))
      break;
  }
  cout << e[i].w;
  return 0;
}
