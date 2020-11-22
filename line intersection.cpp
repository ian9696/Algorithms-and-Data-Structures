/*

line intersection

2016-2017 ACM-ICPC, South Pacific Regional Contest (SPPC 16)
problem D - Dendroctonus
http://codeforces.com/gym/101177

*/

#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;

const double EPS = 1e-8;

struct Point
{
	double x, y;
	double operator-(const Point &r) const
	{
		double dx = x - r.x;
		double dy = y - r.y;
		return sqrt(dx*dx + dy*dy);
	}
	Point operator()(const Point &r) const
	{
		return{ (x + r.x) / 2, (y + r.y) / 2 };
	}
};

struct Line
{
	double a, b, c;
	Line(const Point &p, const Point &q)
	{
		a = q.y - p.y;
		b = p.x - q.x;
		c = -a*p.x - b*p.y;
	}
	Line operator()(const Point &p) const
	{
		Point q = { p.x + a, p.y + b };
		return Line(p, q);
	}
	Point operator*(const Line &r) const
	{
		Point res;
		res.x = (b*r.c - r.b*c) / (a*r.b - r.a*b);
		res.y = (r.a*c - a*r.c) / (a*r.b - r.a*b);
		return res;
	}
};

int check(vector<Point> &v, vector<pair<Point, int>> &I)
{
	Point cen;
	double r;
	if (v.size() == 2)
	{
		cen = v[0](v[1]);
		r = (v[0] - v[1]) / 2;
	}
	else
	{
		Line a = Line(v[0], v[1])(v[0](v[1]));
		Line b = Line(v[1], v[2])(v[1](v[2]));
		if (abs(a.a*b.b - b.a*a.b) < EPS)
			return false;
		cen = a*b;
		r = cen - v[0];
	}
	for (auto &p : I)
		if (p.second && p.first - cen > r + EPS)
			return false;
		else if (!p.second && p.first - cen < r - EPS)
			return false;
	return true;
}

int main()
{
	int n;
	scanf("%d", &n);
	vector<pair<Point, int>> I;
	for (int i = 0; i < n; i++)
	{
		double x, y;
		char s[5];
		scanf("%lf %lf %s", &x, &y, s);
		I.push_back({ { x, y }, s[0] == 'I' });
	}
	if (I.size() <= 2)
	{
		printf("No\n");
		return 0;
	}
	int ans = 0;
	for (int i = 0; i < I.size(); i++)
		for (int j = i + 1; j < I.size(); j++)
		{
			vector<Point> v;
			v.push_back(I[i].first);
			v.push_back(I[j].first);
			if (check(v, I))
				ans = 1;
			for (int k = j + 1; k < I.size(); k++)
			{
				v.push_back(I[k].first);
				if (check(v, I))
					ans = 1;
				v.pop_back();
			}
		}
	printf("%s\n", ans ? "No" : "Yes");
}
