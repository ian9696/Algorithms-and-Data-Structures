/*

length of longest increasing subsequence

*/

#include<stdio.h>
#include<algorithm>
#include<vector>
#include<math.h>
#include<map>
using namespace std;

vector<int> per;
vector<int> ch;

struct Poi
{
	int x, y;
	bool operator<(const Poi &r) const
	{
		return x == r.x && y == r.y ? false : y == r.y ? x < r.x != ch[y] : per[y] < per[r.y];
	}
};

int main()
{
	int n;
	scanf("%d", &n);
	char s[3];
	vector<Poi> v;
	for (int i = 0; i < n; i++)
	{
		scanf("%s", s);
		v.push_back({ s[0] == 'T' ? 10 : s[0] == 'J' ? 11 : s[0] == 'Q' ? 12 : s[0] == 'K' ? 13 : s[0] == 'A' ? 14 : s[0] - '0' , s[1] == 's' ? 0 : s[1] == 'h' ? 1 : s[1] == 'd' ? 2 : 3 });
	}
	per = { 0, 1, 2, 3 };
	int ans = n;
	do
	{
		for (int k = 0; k < (1 << 4); k++)
		{
			ch.clear();
			for (int l = 0; l < 4; l++)
				ch.push_back((k >> l) & 1);
			vector<Poi> vv{ v[0] };
			for (int i = 1; i < n; i++)
				if (vv.back() < v[i])
					vv.push_back(v[i]);
				else
					*lower_bound(vv.begin(), vv.end(), v[i]) = v[i];
			ans = min(ans, n - (int)vv.size());
		}
	} while (next_permutation(per.begin(), per.end()));
	printf("%d\n", ans);
}
