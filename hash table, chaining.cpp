/*

hash table, chaining

Introduction to Algorithms (Fall 2017)
homework4 2Sum using hash table
https://oj.nctu.edu.tw/problems/249/

*/

#include<cstdio>

typedef long long lld;

struct Node
{
    Node *nxt;
    int val;
    lld cnt;
};

const lld P=1e9+7, A=29989, B=1e8+7, M=1e4, N=1e5;
lld a[N];

lld hashval(lld val)
{
    return ((A*val+B)%P+P)%P%M;
}

Node* arr[M];

void add(lld val)
{
    lld h=hashval(val);
    Node *p=arr[h];
    while(p!=NULL && p->val!=val)
        p=p->nxt;
    if(p!=NULL)
    {
        p->cnt++;
        return;
    }
    p=new Node;
    p->nxt=arr[h];
    p->val=val;
    p->cnt=1;
    arr[h]=p;
}

lld query(lld val)
{
    lld h=hashval(val);
    Node *p=arr[h];
    while(p!=NULL && p->val!=val)
        p=p->nxt;
    return p==NULL?0:p->cnt;
}

int main()
{
    int T;
    for(scanf("%d", &T); T>0; T--)
    {
        for(int i=0; i<M; i++)
            arr[i]=NULL;
        int n;
        lld k;
        scanf("%d%lld", &n, &k);
        lld ans=0;
        for(int i=0; i<n; i++)
        {
            scanf("%lld", &a[i]);
            ans+=query(k-a[i]);
            add(a[i]);
        }
        printf("%lld\n", ans);
        for(int i=0; i<M; i++)
        {
            while(arr[i]!=NULL)
            {
                Node *p=arr[i];
                arr[i]=arr[i]->nxt;
                delete p;
            }
        }
    }
}
