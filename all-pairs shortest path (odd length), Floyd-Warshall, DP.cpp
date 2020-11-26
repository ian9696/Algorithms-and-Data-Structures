/*

all-pairs shortest path (odd length), Floyd-Warshall, DP

Introduction to Algorithms (Fall 2018)
Quiz 1.4 Make-Up - Making a Detour (0 points, for practice only)
https://oj.nctu.edu.tw/problems/747/

*/

#include <iostream>

using namespace std;

#define MAX 2147483647

int main(){
	
	int n; cin >> n;
	long long s[n][n];
	long long p[n][n];
	long long o[n][n];

	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			cin >> s[i][j];
			if(s[i][j] == -1){
				s[i][j] = MAX;
			}
			if(i == j){
				s[i][j] = MAX;
			}
		}
	}

	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			if(i == j){
				p[i][j] = 0;
			}else{
				p[i][j] = MAX;
				for(int k=0; k<n; ++k){
					if(k != i && k != j){
						if(p[i][j] > s[i][k]+s[k][j]){
							p[i][j] = s[i][k]+s[k][j];
						}
					}
				}
			}
		}
	}
	
	
	for(int k=0; k<n; ++k){
		for(int i=0; i<n; ++i){
			for(int j=0; j<n; ++j){
				if(p[i][j] > p[i][k]+p[k][j]){
					p[i][j] = p[i][k]+p[k][j];
				}
			}
		}
	}
	

	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			o[i][j] = MAX;
			for(int k=0; k<n; ++k){
				if(s[i][k]+p[k][j] < o[i][j]){
					o[i][j] = s[i][k]+p[k][j];
				}
			}
		}
	}
	
	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
				cout << ((o[i][j] >= MAX) ? -1 : o[i][j]);
				cout << ((j < n-1) ? " " : "\n");
		}
	}

	return 0;
}
