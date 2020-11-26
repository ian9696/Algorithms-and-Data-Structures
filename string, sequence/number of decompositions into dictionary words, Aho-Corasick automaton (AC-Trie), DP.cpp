/*

number of decompositions into dictionary words, Aho-Corasick automaton (AC-Trie), DP

https://www.spoj.com/problems/MORSE/

*/

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<cassert>
using namespace std;

int to(char c)
{
    return c == '.';
}

int dp[10002];


struct actrie{
	struct node{
		node *fl, *nx[26], *dl;
		int cnt, d;
		node(){
			memset(this, 0, sizeof(node));
		}
    } *root;
	actrie(){
		root = new node();
	}
	void add(const char *p){
		node *now=root;
		for(int i=0; p[i]; i++){
			node*& t=now->nx[ to(p[i]) ];
			if( !t ) t=new node();
			now=t;
		}
		now->cnt++;
	}
	void build(){
        queue<node*> Q;
        for(Q.push(root); !Q.empty(); Q.pop()){
            node* now=Q.front();
			for(int i=0; i<2; i++){
				node*& t=now->nx[i], *fn=now->fl;
				if( t ){
					while( fn && !fn->nx[i] ) fn=fn->fl;
                    t->fl= fn ? fn->nx[i] : root ;
                    t->dl= t->fl->cnt ? t->fl : t->fl->dl ;
					t->d=now->d+1; Q.push(t);
				}
			}
		}
	}
	int match(const char *p){
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        
		node* now=root;
		for(int i=0; p[i]; i++){
			while( now && !now->nx[ to(p[i]) ] ) now=now->fl;
			if( !now ) now=root;
            else{
				now=now->nx[ to(p[i]) ];
                for(node *tmp=now; tmp; tmp=tmp->dl)
                    dp[i + 1] += dp[i + 1 - tmp->d] * tmp->cnt;
			}
		}
        
        return dp[strlen(p)];
	}
};


int main()
{
    char A[] = "A .- B -... C -.-. D -.. E . F ..-. G --. H .... I .. J .--- K -.- L .-.. M -- N -. O --- P .--. Q --.- R .-. S ... T - U ..- V ...- W .-- X -..- Y -.-- Z --..";
    char *B[26];
    for (char *p = strtok(A, " "), *pre = NULL; p; pre = p, p = strtok(NULL, " "))
        if (p[0] == '.' || p[0] == '-')
            B[pre[0] - 'A'] = p;
    
    int T;
    for (scanf("%d", &T); T > 0; T--)
    {
        actrie ac;
        char s[10002];
        scanf("%s", s);
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            char w[22], h[82];
            scanf("%s", w);
            for (int j = 0, p = 0; w[j]; j++)
            {
                strcpy(h + p, B[w[j] - 'A']);
                p += strlen(h + p);
            }
            ac.add(h);
        }
        ac.build();
        printf("%d\n", ac.match(s));
    }
}
