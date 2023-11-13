/*

number of connected components in interval (2d grid), disjoint set, index mapping, segment tree (pointer)

Codeforces Round #416 (Div. 2)
E. Vladik and Entertaining Flags
https://codeforces.com/contest/811/problem/E

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

int n, m, q, M[80];
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
	Node *lc, *rc;
	int com, l, r;
	vector<int> lcom, rcom;
	Node()
	{
		lc = rc = NULL;
		com = 1;
		l = r = 0;
	}
} *root;

int reassign(Node *l, Node *r)
{
	for (int i = 0; i < 80; i++)
		M[i] = -1;
	int res = 0, tmp = 0;
	for (int &x : l->rcom)
	{
		int pa = x;
		if (M[pa] == -1)
			M[pa] = tmp++;
		x = M[pa];
		res = max(res, x);
	}
	for (int &x : r->lcom)
	{
		int pa = 40 + x;
		if (M[pa] == -1)
			M[pa] = tmp++;
		x = M[pa];
		res = max(res, x);
	}
	for (int &x : l->lcom)
	{
		int pa = x;
		if (M[pa] == -1)
			M[pa] = tmp++;
		x = M[pa];
		res = max(res, x);
	}
	for (int &x : r->rcom)
	{
		int pa = 40 + x;
		if (M[pa] == -1)
			M[pa] = tmp++;
		x = M[pa];
		res = max(res, x);
	}
	return res + 1;
}

void merge(Node *p, Node *l, Node *r)
{
	int cnt = reassign(l, r);
	DS ds(cnt);
	for (int i = 0; i < n; i++)
		if (v[l->r - 1][i] == v[r->l][i])
			ds.join(l->rcom[i], r->lcom[i]);
	p->lc = l, p->rc = r;
	p->com = l->com + r->com;
	p->l = l->l, p->r = r->r;
	p->lcom = l->lcom, p->rcom = r->rcom;
	for (int &x : p->lcom)
		if (x < cnt)
			x = ds.find(x);
	for (int &x : p->rcom)
		if (x < cnt)
			x = ds.find(x);
	for (int i = 0; i < cnt; i++)
		if (ds.find(i) != i)
			p->com--;
}

Node query(Node *p, int l, int r)
{
	if (p->l == l && p->r == r)
		return *p;
	if (p->lc->r >= r)
		return query(p->lc, l, r);
	if (p->rc->l <= l)
		return query(p->rc, l, r);
	Node res, lt = query(p->lc, l, p->lc->r), rt = query(p->rc, p->rc->l, r);
	merge(&res, &lt, &rt);
	return res;
}


Node* build(int l, int r, vector<vector<int>> &v)
{
	Node *res = new Node;
	res->l = l;
	res->r = r;
	if (r - l == 1)
	{
		res->lcom.resize(n);
		res->rcom.resize(n);
		for (int i = 0; i < n; i++)
		{
			res->lcom[i] = res->rcom[i] = res->com;
			if (i + 1 < n && v[l][i] != v[l][i + 1])
				res->com++;
		}
		return res;
	}
	int m = (l + r) / 2;
	res->lc = build(l, m, v);
	res->rc = build(m, r, v);
	merge(res, res->lc, res->rc);
	return res;
}

int main()
{
	scanf("%d%d%d", &n, &m, &q);
	v.assign(m, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &v[j][i]);
	root = build(0, m, v);
	for (int l, r; q > 0; q--)
	{
		scanf("%d%d", &l, &r);
		l--;
		printf("%d\n", query(root, l, r).com);
	}
}
