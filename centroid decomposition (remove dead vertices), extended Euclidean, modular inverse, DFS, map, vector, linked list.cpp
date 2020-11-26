/*

centroid decomposition (remove dead vertices), extended Euclidean, modular inverse, DFS, map, vector, linked list

Codeforces Round #372 (Div. 1)
C. Digit Tree
https://codeforces.com/contest/715/problem/C

can also be solved by union by size (DSU on tree)

*/

#include<stdio.h>
#include<vector>
#include<map>
using namespace std;

typedef long long lld;

lld M;
lld ans;
bool alive[100000];
lld invtable[100000];
vector<map<lld, lld>> vm;
vector<vector<pair<lld, lld>>> vvcnt;
int level;

struct Edge
{
	int v, w;
	Edge *nxt;
	Edge(int _v, int _w, Edge *_nxt) : v(_v), w(_w), nxt(_nxt) {}
} *E[100000];

int findsize(int x, int p)
{
	int res = 1;
	for (Edge *e = E[x], *pre = NULL; e != NULL; pre = e, e = e->nxt)
		if (alive[e->v] && e->v != p)
			res += findsize(e->v, x);
		else if (e->v == p)
			continue;
		else if (pre == NULL)
			E[x] = e->nxt;
		else
			pre->nxt = e->nxt;
	return res;
}

pair<int, int> findroot(int x, int all, int p)
{
	pair<int, int> res = { 1, x };
	for (Edge *e = E[x], *pre = NULL; e != NULL; pre = e, e = e->nxt)
		if (alive[e->v] && e->v != p)
		{
			pair<int, int> tmp = findroot(e->v, all, x);
			if (tmp.first > all / 2)
				return tmp;
			res.first += tmp.first;
		}
		else if (e->v == p)
			continue;
		else if (pre == NULL)
			E[x] = e->nxt;
		else
			pre->nxt = e->nxt;
	return res;
}

void sol1(int x, pair<lld, lld> sum, lld b, int p, lld d)
{
	sum.first = (sum.first + d * b) % M;
	sum.second = (sum.second * 10 + d) % M;
	b = b * 10 % M;
	vm.back()[sum.first]++;
	vvcnt.back().push_back({ sum.second, level });
	ans += (!sum.first ? 1 : 0) + (!sum.second ? 1 : 0);
	level++;
	for (Edge *e = E[x], *pre = NULL; e != NULL; pre = e, e = e->nxt)
		if (alive[e->v] && e->v != p)
			sol1(e->v, sum, b, x, e->w);
		else if (e->v == p)
			continue;
		else if (pre == NULL)
			E[x] = e->nxt;
		else
			pre->nxt = e->nxt;
	level--;
}

inline lld get(lld z, map<lld, lld> &m)
{
	map<lld, lld>::iterator it = m.find(z);
	return it == m.end() ? 0 : it->second;
}

void ext_gcd(lld a, lld b, lld &x, lld &y)
{
	if (b == 0)
		x = 1, y = 0;
	else
		ext_gcd(b, a%b, y, x), y -= x*(a / b);
}

lld inv(lld a, lld m)
{
	lld x, y;
	ext_gcd(a, m, x, y);
	return (x % m + m) % m;
}

void sol(int x)
{
	int all = findsize(x, -1);
	pair<int, int> tmp = findroot(x, all, -1);
	if (tmp.first > all / 2)
		x = tmp.second;
	vm.clear();
	vvcnt.clear();
	for (Edge *e = E[x], *pre = NULL; e != NULL; pre = e, e = e->nxt)
		if (alive[e->v])
		{
			vm.push_back({});
			vvcnt.push_back({});
			sol1(e->v, { 0, 0 }, 1, x, e->w);
		}
	vm.push_back({});
	for (int i = 0; i < vvcnt.size(); i++)
		for (map<lld, lld>::iterator it = vm[i].begin(); it != vm[i].end(); it++)
			vm.back()[it->first] += it->second;
	for (int i = 0; i < vvcnt.size(); i++)
		for (pair<lld, lld> cnt : vvcnt[i])
		{
			lld z = (-cnt.first * invtable[cnt.second] % M + M) % M;
			ans += get(z, vm.back()) - get(z, vm[i]);
		}
	alive[x] = false;
	for (Edge *e = E[x]; e != NULL; e = e->nxt)
		if (alive[e->v])
			sol(e->v);
}

int main()
{
	int n;
	scanf("%d%lld", &n, &M);
	lld inv10 = inv(10, M);
	invtable[0] = 1;
	for (int i = 1; i < n; i++)
		invtable[i] = invtable[i - 1] * inv10 % M;
	for (int i = 0; i < n; i++)
		E[i] = NULL;
	for (int i = 0, u, v, w; i < n - 1; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		E[u] = new Edge(v, w, E[u]);
		E[v] = new Edge(u, w, E[v]);
	}
	for (int i = 0; i < n; i++)
		alive[i] = true;
	ans = 0, level = 1;
	sol(0);
	printf("%lld\n", ans);
}
