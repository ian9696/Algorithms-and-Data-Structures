/*

DP, record transition path

https://www.hackerrank.com/challenges/arithmetic-expressions/problem

*/

#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1e4;
const int P = 101;
int n, a[N + 2], dp[N + 2][P + 2][2];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    dp[0][a[0]][0] = 123;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < P; j++)
            if (dp[i][j][0])
            {
                dp[i + 1][(j + a[i + 1]) % P][0] = j;
                dp[i + 1][(j + a[i + 1]) % P][1] = '+';
                dp[i + 1][(j - a[i + 1] + P) % P][0] = j;
                dp[i + 1][(j - a[i + 1] + P) % P][1] = '-';
                dp[i + 1][(j * a[i + 1]) % P][0] = j;
                dp[i + 1][(j * a[i + 1]) % P][1] = '*';
            }
    vector<int> v;
    for (int i = n - 1, p = 0; i > 0; p = dp[i][p][0], i--)
        v.push_back(dp[i][p][1]);
    reverse(v.begin(), v.end());
    for (int i = 0; i < n - 1; i++)
        printf("%d%c", a[i], v[i]);
    printf("%d\n", a[n-1]);
}
