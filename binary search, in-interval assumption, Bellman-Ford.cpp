/*

binary search, in-interval assumption, Bellman-Ford

Introduction to Algorithms (Fall 2017)
Quiz3-3. Distance to the Negative Cycle(Practice)
https://oj.nctu.edu.tw/problems/378/

*/

#include <cstdio>

#define N 1000
#define INF 10000000

int dis[1000], threshold;

struct edge{
	int u, v, w;
};

bool BellmanFord(edge *e, int *dis, int n, int m, int s, int (*map)(const edge&)){
	
	for(int i=0; i<n; ++i){
		dis[i] = (i == s) ? 0 : INF;
	}

	for(int i=0; i<n-1; ++i){
		for(int j=0; j<m; ++j){
			if(dis[e[j].v] > dis[e[j].u]+map(e[j])){
				dis[e[j].v] = dis[e[j].u]+map(e[j]);
			}
		}
	}
	for(int j=0; j<m; ++j){
		if(dis[e[j].v] > dis[e[j].u]+map(e[j])){
			return false;
		}
	}
	return true;
}

int allone(const edge &x){
	return 1;
}

int apply(const edge &x){
	return (dis[x.u] < threshold) ? INF : x.w;
}

int main(){
	int n, m, s; scanf("%d%d%d", &n, &m, &s); --s;
	edge e[16000];
	int buf[1000];

	for(int i=0; i<m; ++i){
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		e[i].u --;
		e[i].v --;
	}

	BellmanFord(e, dis, n, m, s, allone);

	threshold = 0;

	if(BellmanFord(e, buf, n, m, s, apply)){
		printf("%d\n", -1);
	}else{
		int L = 0; // return false
		int R = n; // return true
		while(L < R-1){
			int M = (L+R)/2;
			threshold = M;
			if(BellmanFord(e, buf, n, m, s, apply)){
				R = M;
			}else{
				L = M;
			}
		}
		printf("%d\n", L);
	}
}
