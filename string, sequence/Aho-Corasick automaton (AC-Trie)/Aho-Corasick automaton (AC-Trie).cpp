/*

Aho-Corasick automaton (AC-Trie)

*/

#include "stdafx.h"

#include<cstdio>
#include<cstring>

struct actrie
{
	struct node
	{
		node *fl, *nx[26], *dl;
		int cnt, d;
		node()
		{
			memset(this, 0, sizeof(node));
		}
	} *root, *que[100002];
	actrie()
	{
		root = new node();
	}
	void add(char *p)
	{
		node *now = root;
		for (int i = 0; p[i]; i++)
		{
			node *&t = now->nx[p[i] - 'a'];
			if (t == NULL)
				t = new node();
			now = t;
		}
		now->cnt++;
	}
	void build()
	{
		int l = 0, r = 1;
		que[0] = root;
		while (l < r)
		{
			node *now = que[l++];
			for (int i = 0; i < 26; i++)
			{
				node *&t = now->nx[i], *fn = now->fl;
				if (t)
				{
					while (fn && fn->nx[i] == NULL)
						fn = fn->fl;
					if (fn)
						t->fl = fn->nx[i];
					else
						t->fl = root;
					if (t->fl->cnt > 0)
						t->dl = t->fl;
					else
						t->dl = t->fl->dl;
					t->d = now->d + 1;
					que[r++] = t;
				}
			}
		}
	}
	void match(char *p)
	{
		node *now = root;
		for (int i = 0; p[i]; i++)
		{
			while (now && now->nx[p[i] - 'a'] == NULL)
				now = now->fl;
			if (now)
			{
				now = now->nx[p[i] - 'a'];
				node *tmp = now;
				while (tmp)
					tmp = tmp->dl;
			}
			else
				now = root;
		}
	}
};
