/*

persistent segment tree, pointer

http://codeforces.com/contest/484/problem/E

*/

#include"stdafx.h"

#include <stdio.h>
#include <vector>
#include<algorithm>
using namespace std;

const int INF = 0x3FFFFFFF;

struct Node
{
	Node *l, *r;
	int maxseq, preseq, sufseq, siz;
	Node() :l(NULL), r(NULL), maxseq(0), preseq(0), sufseq(0), siz(1){}
};

void merge(Node *p, Node *l, Node *r)
{
	p->maxseq = max(max(l->maxseq, r->maxseq), l->sufseq + r->preseq);
	p->preseq = l->preseq + (l->preseq == l->siz ? r->preseq : 0);
	p->sufseq = r->sufseq + (r->sufseq == r->siz ? l->sufseq : 0);
	p->siz = l->siz + r->siz;
}

Node* build(int n)
{
	if (n == 1)
		return new Node;
	int m = n / 2;
	Node *res = new Node;
	res->l = build(m);
	res->r = build(n - m);
	merge(res, res->l, res->r);
	return res;
}

int size(Node *p)
{
	return p == NULL ? 0 : p->siz;
}

Node* update(Node *pre, int pos)
{
	Node *res = new Node;
	if (pre->l == NULL && pre->r == NULL)
		res->maxseq = res->preseq = res->sufseq = 1;
	else
	{
		if (size(pre->l) > pos)
		{
			res->l = update(pre->l, pos);
			res->r = pre->r;
		}
		else
		{
			res->l = pre->l;
			res->r = update(pre->r, pos -= size(pre->l));
		}
		merge(res, res->l, res->r);
	}
	return res;
}

Node query(Node *p, int l, int r)
{
	if (l == 0 && r >= size(p->l) + size(p->r) - 1)
		return *p;
	if (size(p->l) > r)
		return query(p->l, l, r);
	if (size(p->l) <= l)
		return query(p->r, l - size(p->l), r - size(p->l));
	Node res;
	Node ll = query(p->l, l, size(p->l) - 1);
	Node  rr = query(p->r, 0, r - size(p->l));
	merge(&res, &ll, &rr);
	return res;
}

int main()
{
	int n, m;
	scanf("%d", &n);
	vector<pair<int, int>> h(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &h[i].first), h[i].second = i;
	sort(h.rbegin(), h.rend());
	vector<pair<Node*, int>> roots(n + 1, { NULL, 0 });
	roots[0].first = build(n), roots[0].second = INF;
	for (int i = 0; i < n; i++)
	{
		roots[i + 1].first = update(roots[i].first, h[i].second);
		roots[i + 1].second = h[i].first;
	}
	scanf("%d", &m);
	for (int l, r, w; scanf("%d%d%d", &l, &r, &w) && m; m--)
	{
		l--, r--;
		int ans = 0;
		for (int x = 1, y = n + 1; x < y;)
		{
			int mid = (x + y) / 2;
			if (query(roots[mid].first, l, r).maxseq >= w)
				ans = y = mid;
			else
				x = mid + 1;
		}
		printf("%d\n", roots[ans].second);
	}

	system("pause");
	return 0;
}
