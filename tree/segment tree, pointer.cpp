/*

segment tree, pointer

*/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long ll;
const int INF = 0x3FFFFFFF;
const ll INF2 = 0x3FFFFFFFFFFFFFFFLL;

struct node
{
	int x, y;
	node *l, *r;
	int val, li, ri, all;
	node(int _x, int _y, node *_l, node *_r) :x(_x), y(_y), l(_l), r(_r){}
};

void merge(node *p, node *l, node *r)
{
	p->val = max(l->val, max(r->val, l->ri + r->li));
	p->li = max(l->li, l->all + r->li);
	p->ri = max(r->ri, r->all + l->ri);
	p->all = l->all + r->all;
}

node *build(vector<int> &a, int x, int y)
{
	node *res = NULL;
	if (x == y)
	{
		res = new node(x, y, NULL, NULL);
		res->val = res->li = res->ri = res->all = a[x];
	}
	else
	{
		int m = (x + y) / 2;
		res = new node(x, y, build(a, x, m), build(a, m + 1, y));
		merge(res, res->l, res->r);
	}
	return res;
}

void show(node *p)
{
	if (p == NULL)
		return;
	show(p->l);
	printf("x=%d,y=%d,val=%d\n", p->x, p->y, p->val);
	show(p->r);
}

void modify(node *p, int x, int val)
{
	if (p->x == p->y)
		p->val = p->li = p->ri = p->all = val;
	else
	{
		modify(x <= p->l->y ? p->l : p->r, x, val);
		merge(p, p->l, p->r);
	}
}

node query(node *p, int x, int y)
{
	if (x <= p->x && y >= p->y)
		return *p;
	else
	{
		if (y <= p->l->y)
			return query(p->l, x, y);
		else if (x >= p->r->x)
			return query(p->r, x, y);
		else
		{
			node t(0, 0, NULL, NULL);
			node tl = query(p->l, x, p->l->y);
			node tr = query(p->r, p->r->x, y);
			merge(&t, &tl, &tr);
			return t;
		}
	}
}

int main()
{
	int n, m;
	scanf("%d", &n);
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	node *root = build(a, 1, n);
	//show(root);
	scanf("%d", &m);
	while ((m--) > 0)
	{
		int cmd, x, y;
		scanf("%d%d%d", &cmd, &x, &y);
		if (cmd)
			printf("%d\n", query(root, x, y).val);
		else
			modify(root, x, y);
		//show(root);
	}

	return 0;
}
