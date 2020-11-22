/*

persistent segment tree, array

http://codeforces.com/contest/484/problem/E

*/

#include"stdafx.h"
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

const int INF = 0x3FFFFFFF;

struct Node
{
	int l, r;
	int maxseq, preseq, sufseq, siz;
	Node() :l(-1), r(-1), maxseq(0), preseq(0), sufseq(0), siz(1){}
} nodes[2000000];

int cnt = 0;

void merge(int p, int l, int r)
{
	nodes[p].maxseq = max(max(nodes[l].maxseq, nodes[r].maxseq), nodes[l].sufseq + nodes[r].preseq);
	nodes[p].preseq = nodes[l].preseq + (nodes[l].preseq == nodes[l].siz ? nodes[r].preseq : 0);
	nodes[p].sufseq = nodes[r].sufseq + (nodes[r].sufseq == nodes[r].siz ? nodes[l].sufseq : 0);
	nodes[p].siz = nodes[l].siz + nodes[r].siz;
}

int build(int n)
{
	if (n == 1)
		return cnt++;
	int m = n / 2;
	int res = cnt++;
	nodes[res].l = build(m);
	nodes[res].r = build(n - m);
	merge(res, nodes[res].l, nodes[res].r);
	return res;
}

int size(int p)
{
	return p == -1 ? 0 : nodes[p].siz;
}

int update(int pre, int pos)
{
	int res = cnt++;
	if (nodes[pre].l == -1 && nodes[pre].r == -1)
		nodes[res].maxseq = nodes[res].preseq = nodes[res].sufseq = 1;
	else
	{
		if (size(nodes[pre].l) > pos)
		{
			nodes[res].l = update(nodes[pre].l, pos);
			nodes[res].r = nodes[pre].r;
		}
		else
		{
			nodes[res].l = nodes[pre].l;
			nodes[res].r = update(nodes[pre].r, pos -= size(nodes[pre].l));
		}
		merge(res, nodes[res].l, nodes[res].r);
	}
	return res;
}

int query(int p, int l, int r)
{
	if (l == 0 && r >= size(nodes[p].l) + size(nodes[p].r) - 1)
		return p;
	if (size(nodes[p].l) > r)
		return query(nodes[p].l, l, r);
	if (size(nodes[p].l) <= l)
		return query(nodes[p].r, l - size(nodes[p].l), r - size(nodes[p].l));
	int res = cnt++;
	int ll = query(nodes[p].l, l, size(nodes[p].l) - 1);
	cnt++;
	int  rr = query(nodes[p].r, 0, r - size(nodes[p].l));
	merge(res, ll, rr);
	cnt -= 2;
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
	vector<pair<int, int>> roots(n + 1, { 0, 0 });
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
			if (nodes[query(roots[mid].first, l, r)].maxseq >= w)
				ans = y = mid;
			else
				x = mid + 1;
		}
		printf("%d\n", roots[ans].second);
	}

	system("pause");
	return 0;
}
