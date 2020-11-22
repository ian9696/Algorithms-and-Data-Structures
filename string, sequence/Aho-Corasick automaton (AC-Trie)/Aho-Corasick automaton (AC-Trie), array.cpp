/*

Aho-Corasick automaton (AC-Trie), array

2016-2017 ACM-ICPC Southwestern European Regional Programming Contest (SWERC 2016)
problem E - Passwords
http://codeforces.com/gym/101174

*/

#include "stdafx.h"

#include<cctype>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 1 << 10;
const int M = 1000003;
const char* an = "1234567890qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM";

int convert(int c)
{
	switch (c)
	{
	case '0':
		return 'o';
	case '1':
		return 'i';
	case '3':
		return 'e';
	case '5':
		return 's';
	case '7':
		return 't';
	default:
		return tolower(c);
	}
}

int type(char c)
{
	if ('a' <= c && c <= 'z')
		return 1;
	else if ('A' <= c && c <= 'Z')
		return 2;
	else
		return 4;
}

struct actrie
{
	struct node
	{
		int cnt, d, fl, dl, nx[128];
	} a[1 << 10];

	int n;

	actrie()
	{
		memset(this, 0, sizeof(actrie));
		for (int i = 0; i < N; i++)
		{
			a[i].fl = a[i].dl = -1;
			memset(a[i].nx, 0xFF, sizeof(a[i].nx));
		}
	}

	void add(const char *s)
	{
		int p = 0;

		for (; *s; s++)
		{
			int& t = a[p].nx[convert(*s)];
			if (t == -1) t = ++n;
			p = t;
		}

		a[p].cnt++;
	}

	void build()
	{
		queue<int> Q;

		for (Q.push(0); !Q.empty(); Q.pop())
		{
			int p = Q.front();

			for (int i = 0; i < 128; i++)
			{
				int t = a[p].nx[i], fn = a[p].fl;

				if (t != -1)
				{
					for (; fn != -1 && a[fn].nx[i] == -1; fn = a[fn].fl);
					a[t].fl = fn != -1 ? a[fn].nx[i] : 0;
					a[t].dl = a[a[t].fl].cnt ? a[t].fl : a[a[t].fl].dl;
					a[t].d = a[p].d + 1;
					Q.push(t);
				}
			}
		}
	}

	bool black(int x) const
	{
		return a[x].cnt || a[x].dl != -1;
	}

	int next(int x, int y) const
	{
		int p = x;
		for (y = convert(y); p != -1 && a[p].nx[y] == -1; p = a[p].fl);
		return p != -1 ? a[p].nx[y] : 0;
	}
} T;

int main()
{
	int l, r, n, ans = 0;

	for (scanf("%d%d%d", &l, &r, &n); n > 0; n--)
	{
		char s[32];
		scanf("%s", s);
		T.add(s);
	}

	T.build();
	vector<vector<int>> d(N, vector<int>(8, 0));
	d[0][0] = 1;

	for (int k = 1; k <= r; k++)
	{
		vector<vector<int>> p(N, vector<int>(8, 0));

		for (int i = 0; i <= T.n; i++)
			for (int j = 0; j < 8; j++)
				for (const char* s = an; *s; s++)
				{
					int u = T.next(i, *s);
					int v = j | type(*s);
					p[u][v] += d[i][j];
					if (p[u][v] >= M)
						p[u][v] -= M;
				}

		swap(d, p);

		for (int i = 0; i <= T.n; i++)
		{
			if (T.black(i))
				for (int j = 0; j < 8; j++)
					d[i][j] = 0;

			if (k >= l)
				ans += d[i][7];

			if (ans >= M)
				ans -= M;
		}
	}

	printf("%d\n", ans);
}
