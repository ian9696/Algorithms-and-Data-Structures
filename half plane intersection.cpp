/*

half plane intersection

Codeforces Beta Round #75 (Div. 1 Only)
poblem E - Igloo Skyscraper
http://codeforces.com/contest/91/problem/E

source unknown

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<deque>
#include<cmath>
using namespace std;

#define double long double
#define x first
#define y second

const double EPS = 1e-15;

struct point
{
	double x, y;
	point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
	point operator+(const point &r) const
	{
		return point(x + r.x, y + r.y);
	}
	point operator-(const point &r) const
	{
		return point(x - r.x, y - r.y);
	}
	point operator*(double d) const
	{
		return point(x*d, y*d);
	}
	double operator/(const point &r) const
	{
		return x*r.y - r.x*y;
	}
};

struct line
{
	point p, q;
	int ind;
	line(point _p, point _q, int _ind) : p(_p), q(_q), ind(_ind) {}
};

point interPnt(line l, line l2, bool &res) {
	double f = (l.q - l.p) / (l2.p - l.p);
	double f2 = (l.q - l.p) / (l.p - l2.q);
	double s = f + f2;
	if (fabs(s) < EPS) {
		res = false;
		return{ 0, 0 };
	}
	res = true;
	return l2.p*(f2 / s) + l2.q*(f / s);
}

bool isin(line l, line l1, line l2) {
	// Check inter(l1, l2) in l0
	bool res;
	point p = interPnt(l1, l2, res);
	return (l.q - l.p) / (p - l.p) > EPS;
}

/* If no solution, check: 1. ret.size() < 3
* Or more precisely, 2. interPnt(ret[0], ret[1])
* in all the lines. (use (l.S - l.F).cross(p - l.F) > 0
*/
vector<line> halfPlaneInter(vector<line> lines) {
	int n = lines.size();
	vector<double> ata(n), ord(n);
	for (int i = 0; i < n; i++) {
		ord[i] = i;
		point d = lines[i].q - lines[i].p;
		ata[i] = atan2(d.y, d.x);
	}
	sort(ord.begin(), ord.end(), [&](int i, int j) {
		if (abs(ata[i] - ata[j]) < EPS) {
			return (lines[i].q - lines[i].p) / (lines[j].q - lines[i].p) < 0;
		}
		return ata[i] < ata[j];
	});
	vector<line> fin;
	for (int i = 0; i < n; i++) {
		if (!i || fabs(ata[ord[i]] - ata[ord[i - 1]]) > EPS) {
			fin.push_back(lines[ord[i]]);
		}
	}
	deque<line> dq;
	for (int i = 0; i < fin.size(); i++) {
		while (dq.size() >= 2 && !isin(fin[i], dq[dq.size() - 2], dq[dq.size() - 1]))
			dq.pop_back();
		while (dq.size() >= 2 && !isin(fin[i], dq[0], dq[1]))
			dq.pop_front();
		dq.push_back(fin[i]);
	}
	while (dq.size() >= 3 && !isin(dq[0], dq[dq.size() - 2], dq[dq.size() - 1]))
		dq.pop_back();
	while (dq.size() >= 3 && !isin(dq[dq.size() - 1], dq[0], dq[1]))
		dq.pop_front();
	vector<line> res(dq.begin(), dq.end());
	return res;
}

struct node
{
	node *lc, *rc;
	vector<line> v;
	int l, r;
	node()
	{
		lc = rc = NULL;
	}
};

struct st
{
	node *root;
	st(const vector<line> &v)
	{
		root = build(0, v.size() - 1, v);
	}
	node* build(int l, int r, const vector<line> &v)
	{
		node *res = new node;
		res->l = l, res->r = r;
		res->v = vector<line>(v.begin() + l, v.begin() + r + 1);
		res->v = halfPlaneInter(res->v);
		reverse(res->v.begin(), res->v.end());
		if (l < r)
		{
			int m = (l + r) / 2;
			res->lc = build(l, m, v);
			res->rc = build(m + 1, r, v);
		}
		return res;
	}
	pair<int, double> query(node *p, int l, int r, double t)
	{
		if (p->l == l && p->r == r)
		{
			bool tmp;
			while (p->v.size() >= 2 && interPnt(p->v.back(), p->v[p->v.size() - 2], tmp).x <= t + EPS)
				p->v.pop_back();
			pair<int, double> res;
			line &L = p->v.back();
			return{ L.ind, L.p.y + (L.q.y - L.p.y)*t };
		}
		else if (r <= p->lc->r)
			return query(p->lc, l, r, t);
		else if (p->rc->l <= l)
			return query(p->rc, l, r, t);
		else
		{
			auto res = query(p->lc, l, p->lc->r, t);
			auto tmp = query(p->rc, p->rc->l, r, t);
			return res.y >= tmp.y ? res : tmp;
		}
	}
	int query(int l, int r, double t)
	{
		return query(root, l, r, t).x;
	}
};

struct query
{
	int l, r, ind;
	double t;
	bool operator<(const query &r) const
	{
		return t < r.t;
	}
};

int main()
{
	int n, q;
	scanf("%d%d", &n, &q);
	vector<line> v;
	for (int i = 0; i < n; i++)
	{
		double a, b;
		scanf("%Lf%Lf", &a, &b);
		v.push_back(line(point(0, a), point(1, a + b), i));
	}
	st T(v);
	vector<int> ans(q);
	vector<query> Q(q);
	for (int i = 0; i < q; i++)
	{
		scanf("%d%d%Lf", &Q[i].l, &Q[i].r, &Q[i].t);
		Q[i].l--, Q[i].r--;
		Q[i].ind = i;
	}
	sort(Q.begin(), Q.end());
	for (auto &t : Q)
		ans[t.ind] = T.query(t.l, t.r, t.t);
	for (int t : ans)
		printf("%d\n", t + 1);
}
