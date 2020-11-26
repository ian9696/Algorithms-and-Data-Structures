/*

treap (k-th smallest, size), pointer

Selected Topics in Intractable Problems (Spring 2019)
Set Manipulation (Part I of Programming Assignment #1)
https://oj.nctu.edu.tw/problems/818/

*/

#include<cstdio>
#include<cstdlib>

typedef unsigned long long llu;

struct Node
{
    int ran;
    llu li, ri;
    Node *l, *r;
    llu sum;
    Node(llu _li, llu _ri)
    {
        ran=rand();
        li=_li, ri=_ri;
        l=r=NULL;
        sum=ri-li+1;
    }
    ~Node()
    {
            delete l;
            delete r;
    }
} *root=NULL;

llu get(Node *p)
{
    return p==NULL?0:p->sum;
}

void pull(Node *p)
{
    if(p!=NULL)
        p->sum=(p->ri-p->li+1)+get(p->l)+get(p->r);
}

llu kth(Node *p, llu k)
{
    if(p==NULL)
        return k;
    if(p->li-1-get(p->l)>=k)
        return kth(p->l, k);
    else
        return kth(p->r, k+(p->sum-get(p->r)));
}

void split(Node *p, Node *&l, Node *&r, llu v)
{
    l=r=NULL;
    if(p==NULL)
        return;
    if(p->ri<v)
    {
        split(p->r, l, r, v);
        p->r=l;
        pull(p);
        l=p;
    }
    else
    {
        split(p->l, l, r, v);
        p->l=r;
        pull(p);
        r=p;
    }
}

Node* merge(Node *l, Node *r)
{
    if(l==NULL||r==NULL)
        return l==NULL?r:l;
    if(l->ran<=r->ran)
    {
        l->r=merge(l->r, r);
        pull(l);
        return l;
    }
    else
    {
        r->l=merge(l, r->l);
        pull(r);
        return r;
    }
}

int main()
{
    llu n;
    int U;
    scanf("%llu%d", &n, &U);
    for(; U>0; U--)
    {
        int t;
        scanf("%d", &t);
        if(t==1)
        {
            llu k;
            scanf("%llu", &k);
            printf("%llu\n", kth(root, k));
        }
        else
        {
            llu k, s;
            scanf("%llu%llu", &k, &s);
            llu lv=kth(root, k), rv=kth(root, k-1+s);
            Node *l, *m, *r;
            split(root, l, m, lv);
            split(m, m, r, rv);
            delete m;
            m=new Node(lv, rv);
            root=merge(merge(l, m), r);
        }
    }
}
