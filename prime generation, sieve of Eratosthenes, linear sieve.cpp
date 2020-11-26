/*

prime generation, sieve of Eratosthenes, linear sieve

*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<vector>
#include<string>
#include<string.h>
#include<ctype.h>
using namespace std;

typedef long long lld;

#include<ctime>

vector<int> normal(const int N)
{
	int cnt = 0;
	vector<bool> isp(N, true);
	vector<int> p;
	for (int i = 2; i<N; i++)
	{
		if (isp[i])
		{
			p.push_back(i);
			for (lld j = (lld)i*i; j < N; j += i)
			{
				cnt++;
				isp[j] = false;
			}
		}
	}
	printf("cnt=%d\n", cnt);
	return p;
}

vector<int> linear(const int N)
{
	int cnt = 0;
	vector<bool> isp(N, true);
	vector<int> p;
	for (int i = 2; i<N; i++)
	{
		if (isp[i])
			p.push_back(i);
		for (int j = 0; j < p.size() && (lld)p[j]*i<N; j++)
		{
			cnt++;
			isp[p[j]*i] = false;
			if (i%p[j] == 0)
				break;
		}
	}
	printf("cnt=%d\n",cnt);
	return p;
}

int main(int argc, const char* argv[])
{
	const int N = argc>1 ? atoi(argv[1]) : 1000000;

	time_t t = clock();
	vector<int> prime_n = normal(N);
	printf("%lu\n", clock() - t);

	t = clock();
	vector<int> prime_l = linear(N);
	printf("%lu\n", clock() - t);

	if (prime_n != prime_l)
		printf("Error!\n");
	printf("%d %d\n", prime_n.size(), prime_l.size());
}
