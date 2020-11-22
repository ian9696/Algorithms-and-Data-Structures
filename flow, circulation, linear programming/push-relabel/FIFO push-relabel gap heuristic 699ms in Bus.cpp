
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef long long ll;
const int INF=0x3FFFFFFF;
const ll INF2=0x3FFFFFFFFFFFFFFFLL;

struct Edge
{
	int fr, to, c, f, ind;
	Edge(int _fr, int _to, int _c, int _f, int _ind)
		:fr(_fr), to(_to), c(_c), f(_f), ind(_ind){}
};

vector<ll> shr;
vector<vector<Edge>> adj;
vector<int> e, h;
queue<int> q;
vector<bool> act;
vector<int> cnt;
int n, d, pri;

void addEdge(int fr, int to, int c)
{
	adj[fr].push_back(Edge(fr, to, c, 0, adj[to].size()));
	adj[to].push_back(Edge(to, fr, 0, 0, adj[fr].size()-1));
}

void enqueue(int u)
{
	if(e[u]>0 && !act[u])
	{
		q.push(u);
		act[u]=true;
	}
}

void push(Edge &edge)
{
	int u=edge.fr, v=edge.to;
	int d=min(e[u], edge.c-edge.f);
	if(d==0 || h[u]!=h[v]+1)
		return;
	edge.f+=d;
	adj[v][edge.ind].f-=d;
	e[u]-=d;
	e[v]+=d;
	enqueue(v);
}

void relabel(int u)
{
	cnt[h[u]]--;
	h[u]=INF;
	for(Edge &edge: adj[u])
		if(edge.f<edge.c)
			h[u]=min(h[u], h[edge.to]+1);
	cnt[h[u]]++;
}

void gap(int k)
{
	for(int i=0; i<n+d+2; i++)
		if(h[i]>=k)
		{
			cnt[h[i]]--;
			h[i]=max(h[i], n+d+3);
			cnt[h[i]]++;
		}
		
}

void discharge(int u)
{
	for(int i=0; e[u]>0 && i<(int)adj[u].size(); i++)
		push(adj[u][i]);
	if(e[u]>0)
	{
		if(cnt[h[u]]==1)
			gap(h[u]);
		else
			relabel(u);
		enqueue(u);
	}
}

int main()
{
for(; scanf("%d%d%d", &n, &d, &pri) && n; )
{
	//printf("n : %d, d : %d, pri : %d\n", n, d, pri);
	shr=vector<ll>(n+1, 0);
	adj=vector<vector<Edge>>(n+d+2);
	for(int i=1; i<=d; i++)
	{
		int a;
		scanf("%d", &a);
		for(int j=1; j<=a; j++)
		{
			int b;
			scanf("%d", &b);
			shr[b]+=pri/a;
			addEdge(b, n+i, 1);
		}
	}
	for(int i=1; i<=n; i++)
		addEdge(0, i, 0);
	for(int i=1; i<=d; i++)
		addEdge(n+i, n+d+1, 1);
	e=h=vector<int>(n+d+2, 0);
	act=vector<bool>(n+d+2, false);
	act[0]=act[n+d+1]=true;
	cnt=vector<int>(2*(n+d+2), 0);
	ll ans=INF2;
	for(ll l=0, r=(ll)pri*d+1; l<r; )
	{
		ll m=(l+r)/2;
		//printf("m : %lld\n", m);
		for(int i=0; i<n+d+2; i++)
			for(Edge &edge: adj[i])
				edge.f=0;
		for(Edge &edge: adj[0])
			edge.c=(shr[edge.to]+m)/pri;
		for(int i=0; i<2+n+d; i++)
			e[i]=h[i]=0;
		h[0]=n+d+2;
		for(int i=0; i<2*(n+d+2); i++)
			cnt[i]=0;
		cnt[0]=n+d+1;
		cnt[n+d+2]=1;
		for(Edge &edge: adj[0])
		{
			int d=edge.c;
			edge.f+=d;
			adj[edge.to][edge.ind].f-=d;
			e[0]-=d;
			e[edge.to]+=d;
			enqueue(edge.to);
		}
		while(!q.empty())
		{
			//printf("~\n");
			int u=q.front();
			q.pop();
			act[u]=false;
			discharge(u);
		}
		if(-e[0]==d)
		{
			ans=min(ans, m);
			r=m;
		}
		else
			l=m+1;
	}
	printf("%lld\n", ans);
}		
	return 0;
}

