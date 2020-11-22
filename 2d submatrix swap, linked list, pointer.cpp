/*

2d submatrix swap, linked list, pointer

http://codeforces.com/problemset/problem/706/E

*/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

struct Node
{
	int val;
	Node *r, *d;
	Node(int _val, Node *_r, Node *_d) :val(_val), r(_r), d(_d) {}
};

void mov(Node *&p, int h, int w)
{
	for (int i = 1; i <= h; i++)
		p = p->d;
	for (int i = 1; i <= w; i++)
		p = p->r;
}

void get(Node *&p, int h, int w, vector<pair<Node*, bool>> &res)
{
	for (int i = 1; i <= max(h, w); i++)
		p = h ? p->d : p->r, res.push_back({ p, h });
}
int main()
{
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	vector<Node*> v(n + 2, NULL);
	for (int j = 0; j <= m + 1; j++)
		for (int i = n + 1; i >= 0; i--)
			v[i] = new Node(-1, v[i], (i == n + 1 ? NULL : v[i + 1]));
	for (int i = 1; i <= n; i++)
	{
		Node *p = v[i];
		for (int j = 1, val; j <= m; j++)
			p = p->r, scanf("%d", &p->val);
	}
	for (int a, b, c, d, h, w; q > 0; q--)
	{
		scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &h, &w);
		vector<pair<Node*, bool>> ch, to;
		Node *p3, *p4;
		p3 = p4 = v[0];
		mov(p3, a - 1, b - 1);
		mov(p4, c - 1, d - 1);
		for (int i = 0; i < 2; i++)
		{
			swap(p3, p4);

			Node *p, *p2;
			p = p3, p2 = p4;
			mov(p2, 0, 1);
			get(p, h, 0, ch);
			get(p2, h, 0, to);
			get(p, 0, w, ch);
			get(p2, 1, 0, to);
			get(p2, 0, w - 1, to);

			p = p3, p2 = p4;
			mov(p2, 1, 0);
			get(p, 0, w, ch);
			get(p2, 0, w, to);
			get(p, h, 0, ch);
			get(p2, 0, 1, to);
			get(p2, h - 1, 0, to);
		}
		for (int i = 0; i < ch.size(); i++)
			(ch[i].second ? ch[i].first->r : ch[i].first->d) = to[i].first;
	}
	for (int i = 1; i <= n; i++)
	{
		Node *p = v[i];
		for (int j = 1; j <= m; j++)
			p = p->r, printf("%d ", p->val);
		printf("\n");
	}
}
