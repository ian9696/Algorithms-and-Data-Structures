/*

string with max weight sum (weight w_i if containing word s_i, multiplicity, overlap), Aho-Corasick automaton (AC-Trie), DP, matrix exponentiation by squaring (add, max, max-plus algebra)

Codeforces Round #362 (Div. 1)
D. Legen...
https://codeforces.com/problemset/problem/696/D

*/

#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string>
#include<queue>
using namespace std;

typedef long long int lld;
const lld INF=0x3FFFFFFFFFFFFFFF;

struct Mat
{
    vector<vector<lld> > a;
    int n;
    Mat(int _n):n(_n),a(_n,vector<lld>(_n,0)){}
    Mat operator*(Mat &r)
    {
        Mat res(n);
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            {
                res.a[i][j]=-INF;
                for(int k=0; k<n; k++)
                    res.a[i][j]=max(res.a[i][j], a[i][k]+r.a[k][j]);
            }
        return res;
    }
    Mat operator^(lld p)
    {
        Mat res(n);
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                res.a[i][j]=i==j?0:-INF;
        for(Mat b=*this; p>0; p>>=1, b=b*b)
            if(p&1)
                res=res*b;
        return res;
    }
};

struct node
{
    vector<int> m;
    int suf, dicsuf, par, c;
    vector<int> to;
    string text;
    vector<int> cols;
    bool colv;
    int ind;
    node():m(26, -1),suf(0),dicsuf(0),par(0),c(0),to(26, -1),colv(false),ind(-1){}
};

vector<node> G(1);
vector<string> D;
string T;

void build()
{
    for(int i=0; i<D.size(); i++)
    {
        string &s=D[i];
        int cur=0;
        for(int j=0; j<s.size(); j++)
        {
            int c=s[j]-'a';
            if(G[cur].m[c]==-1)
            {
                G[cur].m[c]=G.size();
                G.push_back(node());
                G.back().par=cur;
                G.back().c=c;
                G.back().text=G[cur].text+(char)(c+'a');
            }
            cur=G[cur].m[c];
        }
        G[cur].ind=i;
    }
    queue<int> q;
    q.push(0);
    while(!q.empty())
    {
        int cur=q.front();
        node &now=G[cur];
        q.pop();
        for(int i=0; i<26; i++)
            if(now.m[i]!=-1)
                q.push(now.m[i]);
        if(cur==0)
            continue;
        int p=G[now.par].suf;
        while(true)
        {
            if(p==0)
            {
                if(G[p].m[now.c]!=-1 && G[p].m[now.c]!=cur)
                    now.suf=G[p].m[now.c];
                break;
            }
            if(G[p].m[now.c]!=-1)
            {
                now.suf=G[p].m[now.c];
                break;
            }
            p=G[p].suf;
        }
    }
    q.push(0);
    while(!q.empty())
    {
        int cur=q.front();
        node &now=G[cur];
        q.pop();
        for(int i=0; i<26; i++)
            if(now.m[i]!=-1)
                q.push(now.m[i]);
        if(cur==0)
            continue;
        int p=G[cur].suf;
        while(p!=0 && G[p].ind==-1)
            p=G[p].suf;
        now.dicsuf=p;
    }
}

int go(int cur, int c)
{
    if(G[cur].to[c]!=-1)
        return G[cur].to[c];
    int ori=cur;
    while(true)
    {
        if(G[cur].m[c]!=-1)
        {
            cur=G[cur].m[c];
            break;
        }
        if(cur==0)
            break;
        cur=G[cur].suf;
    }
    return G[ori].to[c]=cur;
}

vector<int> col(int cur)
{
    if(G[cur].colv)
        return G[cur].cols;
    G[cur].colv=true;
    vector<int> &res=G[cur].cols;
    while(cur!=0)
    {
        if(G[cur].ind!=-1)
            res.push_back(cur);
        cur=G[cur].dicsuf;
    }
    return res;
}

void match()
{
    int  cur=0;
    for(int i=0; i<T.size(); i++)
    {
        printf("~i=%d cur=%d %s\n", i, cur, G[cur].text.c_str());
        cur=go(cur, T[i]-'a');
        printf("cur=%d %s\n", cur, G[cur].text.c_str());
        vector<int> v=col(cur);
        for(int j=0; j<v.size(); j++)
            //printf("%d %s\n", i, D[v[j]].c_str());
            printf("%d %d %s\n", i, v[j], G[v[j]].text.c_str());
    }
}

int main()
{
    int n;
    lld l;
    scanf("%d %lldd", &n, &l);
    vector<int> a(n);
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);
    char s[201];
    for(int i=0; i<n; i++)
    {
        scanf("%s", s);
        D.push_back(s);
    }
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            if(D[i]==D[j])
            {
                a[i]+=a[j];
                swap(a[j], a.back());
                swap(D[j], D.back());
                a.pop_back();
                D.pop_back();
                n--;
                j--;
            }
    build();
    vector<vector<lld> > v(200, vector<lld>(G.size(), 0));
    for(int i=1; i<v.size(); i++)
        for(int j=0; j<G.size(); j++)
            for(int k=0; k<26; k++)
            {
                int to=go(j, k);
                lld t=0;
                vector<int> cols=col(to);
                for(int x=0; x<cols.size(); x++)
                    if(D[G[cols[x]].ind].size()<=i)
                        t+=a[G[cols[x]].ind];
                v[i][to]=max(v[i][to], v[i-1][j]+t);
                if(G[to].text.size()>i)
                    v[i][to]=0;
            }
    if(l<v.size())
    {
        lld ans=0;
        for(int i=0; i<G.size(); i++)
            ans=max(ans, v[l][i]);
        printf("%lld\n", ans);
        return 0;
    }
    l-=v.size()-1;
    vector<int> sum(G.size(), 0);
    for(int i=0; i<G.size(); i++)
    {
        vector<int> cols=col(i);
        for(int j=0; j<cols.size(); j++)
            sum[i]+=a[G[cols[j]].ind];
    }
    Mat mat(G.size());
    for(int i=0; i<G.size(); i++)
        for(int j=0; j<G.size(); j++)
            mat.a[i][j]=-INF;
    for(int i=0; i<G.size(); i++)
        for(int j=0; j<26; j++)
        {
            int to=go(i, j);
            mat.a[to][i]=sum[to];
        }
    mat=mat^l;
    lld ans=0;
    for(int i=0; i<G.size(); i++)
        for(int j=0; j<G.size(); j++)
            ans=max(ans, mat.a[i][j]+v.back()[j]);
    printf("%lld\n", ans);

}
