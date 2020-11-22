/*

heapsort

Introduction to Algorithms (Fall 2017)
homework2.1 heap sort
https://oj.nctu.edu.tw/problems/213/

*/

#include<cstdio>
#include<algorithm>
using namespace std;

const int N=1e5;
int A[N+2], n;

void maxHeapify(int i, int siz)
{
    int l=i*2, r=r=i*2+1, largest=i;
    if(l<=siz && A[l]>A[largest])
        largest=l;
    if(r<=siz && A[r]>A[largest])
        largest=r;
    if(largest!=i)
    {
        swap(A[largest], A[i]);
        maxHeapify(largest, siz);
    }
}

void buildMaxHeap()
{
    for(int i=n/2; i>=1; i--)
        maxHeapify(i, n);
}

void HeapSort()
{
    buildMaxHeap();
    for(int i=1; i<=n; i++)
        printf("%d%s", A[i], (i==n?"\n":" "));
    for(int i=n; i>=2; i--)
    {
        swap(A[1], A[i]);
        maxHeapify(1, i-1);
    }
    for(int i=1; i<=n; i++)
        printf("%d%s", A[i], (i==n?"\n":" "));
}

char s[1000000];

int main()
{
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
        scanf("%d", &A[i]);
    HeapSort();
}
