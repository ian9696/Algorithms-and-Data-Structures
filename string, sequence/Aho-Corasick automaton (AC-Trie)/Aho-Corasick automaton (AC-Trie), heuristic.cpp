/*

Aho-Corasick automaton (AC-Trie), heuristic

http://codeforces.com/problemset/problem/710/F

*/

#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<vector>
using namespace std;

typedef long long lld;

const int X = 647, Y = 547;
char s[700000];

struct node
{
	node *flink, *nxt[26];
	int pcnt, val;
	node()
	{
		memset(this, 0, sizeof(node));
		val = -1;
	}
	~node()
	{
		for (int i = 0; i < 26; i++)
			if (nxt[i])
				delete nxt[i];
	}
} *que[300001];

struct actrie
{
	node *root;
	actrie(vector<char*> &V)
	{
		root = new node;
		for (char *sp : V)
			add(sp);
		build();
	}
	~actrie()
	{
		delete root;
	}
	void add(const char *P)
	{
		node *now = root;
		for (int i = 0; P[i]; i++)
		{
			if (!now->nxt[P[i] - 'a'])
				now->nxt[P[i] - 'a'] = new node;
			now = now->nxt[P[i] - 'a'];
		}
		now->pcnt++;
	}
	void build()
	{
		int front = 0, rear = 1;
		que[front] = root;
		while (front < rear)
		{
			node *now = que[front++], *fnode;
			for (int i = 0; i < 26; i++)
			{
				if (now->nxt[i])
				{
					fnode = now->flink;
					while (fnode && !fnode->nxt[i])
						fnode = fnode->flink;
					now->nxt[i]->flink = fnode ? fnode->nxt[i] : root;
					que[rear++] = now->nxt[i];
				}
			}
		}
	}
	lld query(const char *S)
	{
		lld res = 0;
		node *now = root;
		for (int i = 0; S[i]; i++)
		{
			while (now && !now->nxt[S[i] - 'a'])
				now = now->flink;
			if (now)
			{
				now = now->nxt[S[i] - 'a'];
				res += get(now);
			}
			else
				now = root;
		}
		return res;
	}
	lld get(node *p)
	{
		if (p == root)
			return 0;
		else if (p->val != -1)
			return p->val;
		else
			return p->val = get(p->flink) + p->pcnt;
	}
};

int main()
{
	int m;
	char *sp = s;
	vector<actrie*> VT, VT2;
	vector<vector<char*>> V(1), V2(1);
	vector<int> SIZ(1, 0), SIZ2(1, 0);
	for (scanf("%d", &m); m-- > 0;)
	{
		int t;
		scanf("%d%s", &t, sp);
		int l = strlen(sp);
		if (t == 1)
		{
			V.back().push_back(sp);
			SIZ.back() += l;
			sp += l + 1;
		}
		else if (t == 2)
		{
			V2.back().push_back(sp);
			SIZ2.back() += l;
			sp += l + 1;
		}
		else
		{
			if (V.size() >= X)
			{
				int cnt = 0;
				for (int i = 0; i < V.size() - 1; i++)
				{
					if (SIZ[i] >= max(Y, l / 10))
					{
						V[cnt] = V[i];
						SIZ[cnt] = SIZ[i];
						VT[cnt] = VT[i];
						cnt++;
					}
					else
					{
						V.back().insert(V.back().end(), V[i].begin(), V[i].end());
						SIZ.back() += SIZ[i];
						delete VT[i];
					}
				}
				V[cnt] = V.back();
				SIZ[cnt] = SIZ.back();
				V.resize(cnt + 1);
				SIZ.resize(cnt + 1);
				VT.resize(cnt);
			}
			if (V2.size() >= X)
			{
				int cnt = 0;
				for (int i = 0; i < V2.size() - 1; i++)
				{
					if (SIZ2[i] >= max(Y, l / 10))
					{
						V2[cnt] = V2[i];
						SIZ2[cnt] = SIZ2[i];
						VT2[cnt] = VT2[i];
						cnt++;
					}
					else
					{
						V2.back().insert(V2.back().end(), V2[i].begin(), V2[i].end());
						SIZ2.back() += SIZ2[i];
						delete VT2[i];
					}
				}
				V2[cnt] = V2.back();
				SIZ2[cnt] = SIZ2.back();
				V2.resize(cnt + 1);
				SIZ2.resize(cnt + 1);
				VT2.resize(cnt);
			}
			VT.push_back(new actrie(V.back()));
			VT2.push_back(new actrie(V2.back()));
			V.push_back({});
			V2.push_back({});
			SIZ.push_back(0);
			SIZ2.push_back(0);
			lld res = 0;
			for (actrie *p : VT)
				res += p->query(sp);
			for (actrie *p : VT2)
				res -= p->query(sp);
			printf("%lld\n", res);
			fflush(stdout);
		}
	}
}
