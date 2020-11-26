/*

max length sum of two subsequences (constraints on adjacent elements), DP

O(n^2)

Educational Codeforces Round 22
D. Two Melodies
https://codeforces.com/contest/813/problem/D

*/

#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;

template<class T>
inline void cmax(T& x, int y)
{
    if( x<y )
        x=y;
}

int main()
{
    int n, ans=0;
    scanf("%d", &n);
    vector<int> a(n+1, 0);
    vector<short> d(n+1, 0);
    vector<vector<short>> m(n+1, vector<short>(3, 0));
    vector<vector<short>> p(n+1, vector<short>(7, 0));
    vector<vector<short>> q(n+1, vector<short>(n*3, 0));
    map<int, int> M;
    
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &a[i]);
        
        for(int j=a[i]-1; j<=a[i]+1; j++)
        {
            if( M.find(j)==M.end() )
            {
                int t=M.size();
                M[j]=t;
            }
            
            m[i][ j-a[i]+1 ]=M[j];
        }
        
        a[i]%=7;
        
        for(int j=i-1; j>=0; j--)
        {
            int tmp=max(p[j][ a[i] ], d[j]);
            cmax(tmp, q[j][ m[i][0] ]);
            cmax(tmp, q[j][ m[i][2] ]);
            cmax(ans, ++tmp);
            cmax(p[j][ a[i] ], tmp);
            cmax(q[j][ m[i][1] ], tmp);
            cmax(p[i][ a[j] ], tmp);
            cmax(q[i][ m[j][1] ], tmp);
            d[i]=tmp;
        }
    }
    
    printf("%d\n", ans);
}
