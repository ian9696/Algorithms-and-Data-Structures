#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long ll;

const int INF=0x3FFFFFFF;
const ll INF2=0x3FFFFFFFFFFFFFFFLL;

struct node
{
	int u;
	node *n;
	node(int _u, node *_n):u(_u),n(_n){}
};

int flow(node *&fnt, node *&cur, node *&pre, int n, vector<vector<int>>& c, vector<vector<int>>& f, vector<vector<int>>& adj, vector<int>& e, vector<int>& p, vector<int>& h)
{
	while(cur!=NULL)
	{
		int u=cur->u;
		bool rel=false;
		while(e[u]>0)
		{
			if(p[u]==(int)adj[u].size())
			{
				rel=true;
				int minh=INF;
				for(int w: adj[u])
					if(c[u][w]>f[u][w])
						minh=min(minh, h[w]);
				h[u]=minh+1;
				p[u]=0;
			}
			int v=adj[u][p[u]];
			if(c[u][v]>f[u][v] && h[u]==h[v]+1)
			{
				int d=min(e[u], c[u][v]-f[u][v]);
				f[u][v]+=d;
				f[v][u]-=d;
				e[u]-=d;
				e[v]+=d;
			}
			else
				p[u]++;
		}
		if(rel && pre!=NULL)
		{
			pre->n=cur->n;
			cur->n=fnt;
			fnt=cur;
			pre=NULL;
			
		}
		pre=cur;
		cur=cur->n;
	}
	int ans=0;
	for(int i=1; i<=n; i++)
		ans+=f[0][i];
	return ans;
}

int main()
{
for(int n, d, pri; scanf("%d%d%d", &n, &d, &pri) && n; )
{
	//printf("n : %d, d : %d, pri : %d\n", n, d, pri);
	vector<ll> shr(n+1, 0);
	vector<vector<int>> c(2+n+d, vector<int>(2+n+d, 0)), f(2+n+d, vector<int>(2+n+d, 0)), adj(2+n+d);
	vector<int> e(2+n+d, 0), p(2+n+d, 0), h(2+n+d, 0);
	for(int i=1; i<=d; i++)
	{
		int a;
		scanf("%d", &a);
		for(int j=1; j<=a; j++)
		{
			int b;
			scanf("%d", &b);
			shr[b]+=pri/a;
			c[b][n+i]=1;
			adj[b].push_back(n+i);
			adj[n+i].push_back(b);
		}
	}
	for(int i=1; i<=d; i++)
	{
		c[n+i][n+d+1]=1;
		adj[n+i].push_back(n+d+1);
	}
	h[0]=2+n+d;
	node *fnt, *cur, *pre;
	fnt=cur=pre=NULL;
	for(int i=1; i<=n+d; i++)
		fnt = new node(i, fnt);
	ll ans=INF2;
	for(ll l=0, r=(ll)pri*d+1; l<r; )
	{
		ll m=(l+r)/2;
		cur=fnt;
		pre=NULL;
		for(int i=0; i<2+n+d; i++)
			for(int j=0; j<n+d+2; j++)
				f[i][j]=0;
		for(int i=0; i<2+n+d; i++)
			e[i]=0;
		for(int i=1; i<=n; i++)
		{
			int d=(shr[i]+m)/pri;
			if(adj[i].size()>0 && adj[i].back()==0)
				adj[i].pop_back();
			if(d>0)
				adj[i].push_back(0);
			c[0][i]=d;
			f[0][i]=d;
			f[i][0]=-d;
			e[0]-=d;
			e[i]+=d;
		}
		for(int i=1; i<=n+d; i++)
			p[i]=h[i]=0;
		if(flow(fnt, cur, pre, n, c, f, adj, e, p, h)==d)
		{
			ans=min(ans, m);
			r=m;
		}
		else
			l=m+1;
	}
	while(fnt!=NULL)
	{
		pre=fnt;
		fnt=fnt->n;
		delete pre;
	}
	printf("%lld\n", ans);
}		
	return 0;
}

