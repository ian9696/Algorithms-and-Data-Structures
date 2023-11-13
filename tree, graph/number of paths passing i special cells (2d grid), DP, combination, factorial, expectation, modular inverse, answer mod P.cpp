/*

number of paths passing i special cells (2d grid), DP, combination, factorial, expectation, modular inverse, answer mod P

Intel Code Challenge Elimination Round (Div. 1 + Div. 2, combined)
E. Research Rover
https://codeforces.com/contest/722/problem/E

Intel Code Challenge Elimination Round (div.1 + div.2 combined) editorial
https://codeforces.com/blog/entry/47497

*/

#include<stdio.h>
#include<algorithm>
#include<vector>
#include<string.h>
using namespace std;

typedef long long lld;
const lld P = 1000000007;

int n, m, k, s;
lld F[200000][2];
lld dp[2][2001];

inline lld inv(lld a)
{
    lld res = 1;
    for (lld b = a, p = P - 2; p > 0; p /= 2, b = b*b%P)
    if (p & 1)
        res = res*b%P;
    return res;
}

inline lld com(lld a, lld b)
{
    return F[a][0] * F[b][1] % P*F[a - b][1] % P;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &k, &s);
    F[0][0] = F[0][1] = 1;
    for (int i = 1; i <= n + m - 2; i++)
        F[i][0] = F[i - 1][0] * i%P, F[i][1] = inv(F[i][0]);
    vector<vector<lld>> a;
    bool flag = false;
    for (int i = 0, r, c; i < k; i++)
    {
        scanf("%d%d", &r, &c);
        a.push_back({ r + c, r, c });
        flag |= a.back() == vector<lld>{2, 1, 1};
    }
    if (!flag)
        a.push_back({ 2, 1, 1 }), k++;
    sort(a.begin(), a.end());
    memset(dp, 0, sizeof(dp));
    lld ans = 0, cnt = 0;
    if (flag)
        s = (s + 1) / 2;
    for (; s > 1; s = (s + 1) / 2)
    {
        for (int j = k - 1; j >= 0; j--)
        {
            lld x = a[j][1], y = a[j][2];
            lld &res = dp[0][j];
            res = com(n - x + m - y, n - x);
            for (int l = j + 1; l < k; l++)
            if (x <= a[l][1] && y <= a[l][2])
                res = (res + P - com(a[l][1] - x + a[l][2] - y, a[l][1] - x)*dp[0][l] % P) % P;
            res = (res + P - dp[1][j]) % P;
            dp[1][j] = (dp[1][j] + res) % P;
        }
        ans = (ans + s*dp[0][0] % P) % P;
        cnt = (cnt + dp[0][0]) % P;
    }
    ans = (ans + com(n - 1 + m - 1, n - 1) + P - cnt) % P;
    ans = ans*inv(com(n - 1 + m - 1, n - 1)) % P;
    printf("%lld\n", ans);
}
