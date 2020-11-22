/*

quicksort

Introduction to Algorithms (Fall 2017)
homework2.2 quick sort
https://oj.nctu.edu.tw/problems/214/
*/

#include<cstdio>
#include<algorithm>
#include<set>
#include<cassert>
using namespace std;

const int N=1e3;
int A[N+2], n, ans;

int Partition(int p, int r)
{
    int i=p-1;
    for(int j=p; j<=r-1; j++)
        if(A[j]<=A[r])
        {
            i++;
            swap(A[i], A[j]);
        }
    swap(A[i+1], A[r]);
    return i+1;
}

void Quicksort(int p, int r)
{
    if(p>=r)
        return;
    int q=Partition(p, r);
    if(q>p && q<r)
        ans=0;
    Quicksort(p, q-1);
    Quicksort(q+1, r);

}

int main()
{
    int T;
    for(scanf("%d", &T); T>0; T--)
    {
        scanf("%d", &n);
        set<int> S;
        for(int i=1; i<=n; i++)
            scanf("%d", &A[i]), S.insert(A[i]);
        assert(S.size()==n);
        ans=1;
        Quicksort(1, n);
        printf("%s\n", ans?"Yes":"No");
        for(int i=1; i<=n; i++)
            printf("%d%s", A[i], (i==n?"\n":" "));
    }
}
