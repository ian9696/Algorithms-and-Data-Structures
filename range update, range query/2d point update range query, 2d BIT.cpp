/*

2d point update range query, 2d BIT

*/

#include "stdafx.h"

#include<iostream>
#include<vector>
using namespace std;

struct Bit
{
	int w, h;//1<=x<=w, 1<=y<=h
	vector<vector<int>> a;
	Bit(int w, int h) :w(w), h(h), a(w + 1, vector<int>(h + 1, 0)){}
	void add(int x, int y, int val)
	{
		for (; x <= w; x += x&-x)
			for (int yy = y; yy <= h; yy += yy&-yy)
				a[x][yy] += val;
	}
	int query(int x, int y)
	{
		int res = 0;
		for (; x > 0; x -= x&-x)
			for (int yy = y; yy > 0; yy -= yy&-yy)
				res += a[x][yy];
		return res;
	}
};

int main()
{
	int w, h;
	scanf("%d%d", &w, &h);
	Bit bit(w, h);
	while (true)
	{
		int cmd, x, y, val;
		scanf("%d%d%d", &cmd, &x, &y);
		if (cmd)
		{
			scanf("%d", &val);
			bit.add(x, y, val);
		}
		else
			printf("%d\n", bit.query(x, y));
	}
	return 0;
}
