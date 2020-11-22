/*

treap, parent link

http://codeforces.com/gym/100796/problem/J

*/

#include "stdafx.h"

#include<stdio.h>
#include<algorithm>
#include<vector>
#include<stdlib.h>
using namespace std;

struct treap
{
	struct node
	{
		int siz, pri;
		node *l, *r, *pa;
		node() { siz = 1, pri = rand(), l = r = pa = NULL; }
	} *root;
	int cnt;
	vector<node*> pos;
	treap() { root = NULL, cnt = 0; }
	int get(node *p)
	{
		return p == NULL ? 0 : p->siz;
	}
	void pull(node *p)
	{
		p == NULL ? 0 : p->siz = get(p->l) + 1 + get(p->r);
	}
	void setpa(node *p, node *pa)
	{
		p == NULL ? 0 : p->pa = pa;
	}
	void split(node *p, int k, node *&l, node *&r)
	{
		if (p == NULL)
			l = r = NULL;
		else if (get(p->l) >= k)
			setpa(p->l, NULL), split(p->l, k, l, r), p->l = r, setpa(p->l, p), pull(p), r = p;
		else
			setpa(p->r, NULL), split(p->r, k - get(p->l) - 1, l, r), p->r = l, setpa(p->r, p), pull(p), l = p;
	}
	void merge(node *l, node *r, node *&p)
	{
		if (l == NULL)
			p = r;
		else if (r == NULL)
			p = l;
		else if (l->pri > r->pri)
			setpa(l->r, NULL), merge(l->r, r, l->r), setpa(l->r, l), pull(l), p = l;
		else
			setpa(r->l, NULL), merge(l, r->l, r->l), setpa(r->l, r), pull(r), p = r;
	}
	void insert(bool x)
	{
		cnt++;
		pos.push_back(new node());
		merge((x ? pos.back() : root), (x ? root : pos.back()), root);
	}
	int query(int x)
	{
		cnt--;
		node *p = pos[x], *l, *r;
		int siz = get(p->l);
		while (p->pa != NULL)
			siz += p->pa->l == p ? 0 : get(p->pa->l) + 1, p = p->pa;
		split(root, siz, l, r);
		split(r, 1, p, r);
		merge(r, l, root);
		return min(siz, cnt - siz);
	}
};

int main()
{
	int n;
	scanf("%d", &n);
	treap T;
	for (int i = 0, x; i < n; i++)
	{
		char c;
		scanf(" %c", &c);
		if (c == 'F')
			T.insert(1);
		else if (c == 'B')
			T.insert(0);
		else
			scanf("%d", &x), printf("%d\n", T.query(x - 1));
	}
}
