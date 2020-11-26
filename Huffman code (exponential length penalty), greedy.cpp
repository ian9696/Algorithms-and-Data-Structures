/*

Huffman code (exponential length penalty), greedy

Introduction to Algorithms (Fall 2018)
Quiz 1.1 - Another Huffman Code (0 points, for practice only)
https://oj.nctu.edu.tw/problems/739/

*/

#include<cstdio>
#include<queue>
using namespace std;

typedef long long lld;

int main()
{
    int n;
    scanf("%d", &n);
    priority_queue<lld> pq;
    for(int i=0; i<n; i++)
    {
        lld x;
        scanf("%lld", &x);
        pq.push(-x);
    }
    for(int i=0; i<n-1; i++)
    {
        lld x=pq.top();
        pq.pop();
        lld y=pq.top();
        pq.pop();
        pq.push(2*(x+y));

    }
    printf("%lld\n", -pq.top());
}
