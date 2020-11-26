/*

Huffman code (min max weighted path length), greedy

Introduction to Algorithms (Fall 2018)
Assignment 14 - Merging Sets (Deadline: 11/24 23:59:59)
https://oj.nctu.edu.tw/problems/679/

*/

#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

int main()
{
    int d, n;
    scanf("%d%d", &d, &n);
    priority_queue<int> pq;
    for(int i=0; i<n; i++)
    {
        int w;
        scanf("%d", &w);
        pq.push(w);
    }
    for(int i=0; i<n-1; i++)
    {
        int l=pq.top();
        pq.pop();
        int r=pq.top();
        pq.pop();
        pq.push(max(l, r)-d);
    }
    printf("%d\n", pq.top());
}
