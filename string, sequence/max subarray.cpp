/*

max subarray

Introduction to Algorithms (Fall 2018)
Assignment 2 - Maximum Subarray (Deadline: 9/29 23:59:59)
https://oj.nctu.edu.tw/problems/652/

*/

#include<iostream>
#include<algorithm>
using namespace std;

typedef long long lld;

int main()
{
	int n;
	cin>>n;
	lld ans=0, p=0;
	for(int x; n>0; n--)
	{
		cin>>x;
		p=max(p+x, (lld)x);
		ans=max(ans, p);
	}
	cout<<ans<<endl;
}
