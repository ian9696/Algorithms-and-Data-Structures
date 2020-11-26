/*

2d rectangle overlap, coordinate mapping, segment tree (1d range update all query, 1d point update prefix query), pointer

Selected Topics in Intractable Problems (Spring 2019)
Not So Helly (Programming Assignment #3)
https://oj.nctu.edu.tw/problems/929/

*/

#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<cstring>
using namespace std;

struct Event
{
    int x, b, t, val;
    Event(int _x, int _b, int _t, int _val): x(_x),b(_b),t(_t),val(_val) {}
    bool operator<(const Event &r) const
    {
        return x<r.x;
    }
};

struct Node
{
    Node *l, *r;
    int siz, val, sum, ans;
    Node()
    {
        memset(this, 0, sizeof(Node));
    }
};

Node* build(int n)
{
    Node *p=new Node();
    p->siz=n;
    if(n>1)
    {
        int lsiz=n/2;
        p->l=build(lsiz);
        p->r=build(n-lsiz);
    }
    return p;
}

void add(Node *p, int x, int val)
{
    if(p->siz==1)
    {
        p->val=p->sum=p->ans=p->val+val;
        return;
    }
    if(p->l->siz>x)
        add(p->l, x, val);
    else
        add(p->r, x-p->l->siz, val);
    p->sum=p->l->sum+p->r->sum;
    p->ans=max(p->l->ans, p->l->sum+p->r->ans);
}

int main()
{
    vector<Event> E;
    map<int, int> M;
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        int l, r, b, t;
        scanf("%d%d%d%d", &l, &r, &b, &t);
        M[b]=M[t]=0;
        E.push_back(Event(l, b, t, 1));
        E.push_back(Event(r+1, b, t, -1));
    }
    int cnt=0;
    for(pair<const int, int> &t: M)
        t.second=cnt++;
    for(Event &event: E)
    {
        event.b=M[event.b];
        event.t=M[event.t];
    }
    sort(E.begin(), E.end());
    int t=0, ans=0;
    Node *root=build(M.size()+1);
    while(t<E.size())
    {
        int s=t;
        while(t<E.size() && E[s].x==E[t].x)
        {
            add(root, E[t].b, E[t].val);
            add(root, E[t].t+1, -E[t].val);
            ans=max(ans, root->ans);
            t++;
        }
    }
    printf("%d\n", ans);
}