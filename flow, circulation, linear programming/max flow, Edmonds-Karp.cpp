/*

max flow, Edmonds-Karp

*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

typedef long long ll;
const int INF = 0x3FFFFFFF;
const ll INF2 = 0x3FFFFFFFFFFFFFFFLL;

int main()
{
    int k;
    scanf("%d", &k);
    while ((k--) > 0)
    {
        int p, t, s, c;
        scanf("%d%d%d%d", &p, &t, &s, &c);
        vector<vector<int>> pos(p + t + 1, vector<int>(2));
        for (int i = 1; i <= p + t; i++)
            scanf("%d%d", &pos[i][0], &pos[i][1]);
        vector<vector<int>> f(p + t + 2, vector<int>(p + t + 2, 0));
        vector<vector<int>> ca = f;
        vector<vector<int>> adj(p + t + 2);
        for (int i = 1; i <= p; i++)
            for (int j = p + 1; j <= p + t; j++)
                if (200 * (abs(pos[i][0] - pos[j][0]) + abs(pos[i][1] - pos[j][1])) <= c * s)
                {
                    ca[i][j] = 1;
                    adj[i].push_back(j);
                }
        for (int i = 1; i <= p; i++)
        {
            ca[0][i] = 1;
            adj[0].push_back(i);
        }
        for (int i = p + 1; i <= p + t; i++)
        {
            ca[i][p + t + 1] = 1;
            adj[i].push_back(p + t + 1);
        }
        int ans = 0;
        while (true)
        {
            vector<int> pre(p + t + 2, -1);
            queue<pair<int, int>> q;
            for (q.push(pair<int, int>(0, 0)); !q.empty(); q.pop())
            {
                if (pre[q.front().first] == -1)
                {
                    int u = q.front().first;
                    pre[u] = q.front().second;
                    if (u == p + t + 1)
                        break;
                    for (int v : adj[u])
                        q.push(pair<int, int>(v, u));
                }
            }
            if (pre[p + t + 1] == -1)
                break;
            int minc = INF;
            for (int u = p + t + 1; u != 0; u = pre[u])
                minc = min(minc, ca[pre[u]][u] - f[pre[u]][u]);
            ans += minc;
            for (int v = p + t + 1; v != 0; v = pre[v])
            {
                int u = pre[v];
                if (f[v][u] == ca[v][u])
                    adj[v].push_back(u);
                f[u][v] += minc;
                f[v][u] = -f[u][v];
                if (f[u][v] == ca[u][v])
                    for (int i = 0; i < adj[u].size(); i++)
                        if (adj[u][i] == v)
                            adj[u].erase(adj[u].begin() + i);
            }
        }
        printf("%d\n", ans);
    }

    system("pause");
    return 0;
}
