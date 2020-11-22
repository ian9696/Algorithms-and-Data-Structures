/*

L0-sampler

Streaming Algorithms (Spring 2018)
3. L0 Sampler
https://oj.nctu.edu.tw/problems/579/

*/

#include<cstdlib>
#include<algorithm>
#include<set>
using namespace std;

#define lld long long
#define i128 __int128

const lld P = 1e9 + 7;
const int K = 1, W = 1900000, R = 10;
int n, m, ab[W][2], a[R], b[R];

struct ut
{
	int a;
	lld b;
	i128 c;
	ut()
	{
		a = b = c = 0;
	}
} un[W][K];

lld randLldModP()
{
	return ((lld)rand() << 30 ^ (lld)rand() << 15 ^ rand()) % P;
}

void sol()
{
	for (int i = 0; i < R; i++)
	{
		a[i] = randLldModP();
		b[i] = randLldModP();
	}
	for (int x, u, v, e; m > 0; m--)
	{
		x = io.next_int();
		u = abs(x) & 0x7FFF, v = abs(x) >> 15;
		if (u == v)
			continue;
		if (u > v)
			swap(u, v);
		e = u << 15 | v;
		x = x > 0 ? 1 : -1;

		for (int i = 0; i < R; i++)
		{
			int ind = ((lld)a[i] * e + b[i]) % P % W;
			int ind2 = ((lld)ab[ind][0] * e + ab[ind][1]) % P%K;
			un[ind][ind2].a += x;
			un[ind][ind2].b += x*e;
			un[ind][ind2].c += (lld)x*e*e;
		}
	}
	set<int> S;
	for (int i = 0; i < W; i++)
		for (int j = 0; j < K; j++)
			if (un[i][j].a && un[i][j].a*un[i][j].c == (i128)un[i][j].b*un[i][j].b)
				S.insert(un[i][j].b / un[i][j].a);
	for (; !S.empty(); S.erase(S.begin()))
		printf("%d %d\n", *S.begin() >> 15, *S.begin() & 0x7FFF);
}

int main()
{
	n = io.next_int(), m = io.next_int();
	sol();
}
