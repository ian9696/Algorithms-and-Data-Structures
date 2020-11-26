/*

centroid decomposition, extended Euclidean, modular inverse, DFS, map, vector

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
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<VVI> VVVI;
typedef vector<lld> VLL;
typedef vector<VLL> VVLL;
typedef vector<VVLL> VVVLL;

int n;
lld M;
vector<vector<pair<int, int>>> e;
lld ans;
bool alive[100000];
lld invtable[100000];

int findsize(int x, int p)
{
	int res = 1;
	for (pair<int, int> pa : e[x])
		if (alive[pa.first] && pa.first != p)
			res += findsize(pa.first, x);
	return res;
}

pair<int, int> findroot(int x, int all, int p)
{
	pair<int, int> res = { 1, x };
	for (pair<int, int> pa : e[x])
		if (alive[pa.first] && pa.first != p)
		{
			pair<int, int> tmp = findroot(pa.first, all, x);
			if (tmp.first > all / 2)
				return tmp;
			res.first += tmp.first;
		}
	return res;
}

void sol1(int x, pair<lld, lld> sum, lld b, int p, lld d, map<lld, lld> &m, vector<pair<lld, lld>> &vcnt, int level)
{
	sum.first = (sum.first + d * b) % M;
	sum.second = (sum.second * 10 + d) % M;
	b = b * 10 % M;
	m[sum.first]++;
	vcnt.push_back({ sum.second, level });
	ans += (!sum.first ? 1 : 0) + (!sum.second ? 1 : 0);
	for (pair<int, int> pa : e[x])
		if (alive[pa.first] && pa.first != p)
			sol1(pa.first, sum, b, x, pa.second, m, vcnt, level + 1);
}

inline lld get(lld z, map<lld, lld> &m)
{
	map<lld, lld>::iterator it = m.find(z);
	return it == m.end() ? 0 : it->second;
}

lld ext_gcd(lld a, lld b, lld &x, lld &y)
{
	if (b == 0)
	{
		x = 1, y = 0;
		return a;
	}
	lld r = ext_gcd(b, a%b, y, x);
	y -= x*(a / b);
	return r;
}

lld inv(lld a, lld m)
{
	lld x, y;
	ext_gcd(a, m, x, y);
	return (x % m + m) % m;
}

void sol(int x)
{
	//printf("sol x=%d\n", x);
	int all = findsize(x, -1);
	//printf("findsize finished all=%d\n", all);
	pair<int, int> tmp = findroot(x, all, -1);
	//printf("findroot finished\n tmp=%d %d\n", tmp[0], tmp[1]);
	if (tmp.first > all / 2)
		x = tmp.second;
	vector<map<lld, lld>> vm;
	vector<vector<pair<lld, lld>>> vvcnt;
	for (pair<int, int> p : e[x])
		if (alive[p.first])
		{
			vm.push_back({});
			vvcnt.push_back({});
			sol1(p.first, { 0, 0 }, 1, x, p.second, vm.back(), vvcnt.back(), 1);
		}
	//printf("!!!x=%d ans=%lld\n", x, ans);
	//printf("sol1 finished\n");
	vm.push_back({});
	for (int i = 0; i < vvcnt.size(); i++)
		for (map<lld, lld>::iterator it = vm[i].begin(); it != vm[i].end(); it++)
			vm.back()[it->first] += it->second;
	for (int i = 0; i < vvcnt.size(); i++)
		for (pair<lld, lld> cnt : vvcnt[i])
		{
			lld z = (-cnt.first * invtable[cnt.second] % M + M) % M;
			ans += get(z, vm.back()) - get(z, vm[i]);
			//printf("#ans=%lld cnt0=%lld cnt1=%lld z=%lld %lld %lld\n", ans, cnt[0], cnt[1], z, get(z, vm.back()), get(z, vm[i]));
		}
	//printf("!!!x=%d ans=%lld\n", x, ans);
	//printf("~~~x=%d\n", x);
	alive[x] = false;
	for (pair<int, int> p : e[x])
		if (alive[p.first])
			sol(p.first);
	//printf("sol finished x=%d\n", x);
}
int main()
{
	scanf("%d%lld", &n, &M);
	lld inv10 = inv(10, M);
	invtable[0] = 1;
	for (int i = 1; i < n; i++)
		invtable[i] = invtable[i - 1] * inv10 % M;
	e.resize(n);
	for (int i = 0, u, v, w; i < n - 1; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back({ v, w });
		e[v].push_back({ u, w });
	}
	for (int i = 0; i < n; i++)
		alive[i] = true;
	ans = 0;
	sol(0);
	printf("%lld\n", ans);
}
