/*

number of connected components in interval (2d grid), disjoint set, index mapping, segment tree (array)

Codeforces Round #416 (Div. 2)
E. Vladik and Entertaining Flags
https://codeforces.com/contest/811/problem/E

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

int n, m, q, use, M[80];
vector<vector<int>> v;

struct DS
{
	int n;
	vector<int> a;
	DS(int _n)
	{
		n = _n;
		a.resize(n);
		for (int i = 0; i < n; i++)
			a[i] = i;
	}
	int find(int x)
	{
		return a[x] == x ? x : a[x] = find(a[x]);
	}
	void join(int x, int y)
	{
		x = find(x);
		y = find(y);
		a[x] = y;
	}
};

struct Node
{
	int lc, rc;
	int com, l, r;
	int lcom[10], rcom[10];
	Node()
	{
		lc = rc = 0;
		com = 1;
		l = r = 0;
	}
} P[300000];

int reassign(int lind, int rind)
{
	Node &l = P[lind];
	Node &r = P[rind];
	int *arr[] = { l.rcom, r.lcom, l.lcom, r.rcom };
	for (int i = 0; i < 80; i++)
		M[i] = -1;
	int res = 0, tmp = 0;
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < n; i++)
		{
			int &x = arr[j][i];
			int ind = (j & 1) * 40 + x;
			if (M[ind] == -1)
				M[ind] = tmp++;
			x = M[ind];
			if (j < 2)
				res = max(res, x);
		}
	return res + 1;
}

void merge(int pind, int lind, int rind)
{
	Node &p = P[pind];
	Node &l = P[lind];
	Node &r = P[rind];
	int cnt = reassign(lind, rind);
	DS ds(cnt);
	for (int i = 0; i < n; i++)
		if (v[l.r - 1][i] == v[r.l][i])
			ds.join(l.rcom[i], r.lcom[i]);
	p.lc = lind, p.rc = rind;
	p.com = l.com + r.com;
	p.l = l.l, p.r = r.r;
	for (int i = 0; i < n; i++)
		p.lcom[i] = l.lcom[i], p.rcom[i] = r.rcom[i];
	int *arr[] = { p.lcom, p.rcom };
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < n; i++)
		{
			int &x = arr[j][i];
			if (x < cnt)
				x = ds.find(x);
		}
	for (int i = 0; i < cnt; i++)
		if (ds.find(i) != i)
			p.com--;
}

int query(int pind, int lb, int rb)
{
	Node &p = P[pind];
	if (p.l == lb && p.r == rb)
		return pind;
	Node &l = P[p.lc];
	Node &r = P[p.rc];
	if (l.r >= rb)
		return query(p.lc, lb, rb);
	if (r.l <= lb)
		return query(p.rc, lb, rb);
	int res = use++;
	int lt = query(p.lc, lb, l.r);
	use++;
	int rt = query(p.rc, r.l, rb);
	merge(res, lt, rt);
	use -= 2;
	return res;
}


int build(int l, int r, vector<vector<int>> &v)
{
	int resind = use++;
	Node &res = P[resind];
	res.l = l;
	res.r = r;
	if (r - l == 1)
	{
		for (int i = 0; i < n; i++)
		{
			res.lcom[i] = res.rcom[i] = res.com;
			if (i + 1 < n && v[l][i] != v[l][i + 1])
				res.com++;
		}
		return resind;
	}
	int m = (l + r) / 2;
	res.lc = build(l, m, v);
	res.rc = build(m, r, v);
	merge(resind, res.lc, res.rc);
	return resind;
}

int main()
{
	scanf("%d%d%d", &n, &m, &q);
	v.assign(m, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &v[j][i]);
	build(0, m, v);
	for (int l, r; q > 0; q--)
	{
		scanf("%d%d", &l, &r);
		l--;
		printf("%d\n", P[query(0, l, r)].com);
	}
}
