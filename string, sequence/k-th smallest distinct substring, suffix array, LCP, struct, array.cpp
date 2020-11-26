/*

k-th smallest distinct substring, suffix array, LCP, struct, array

O(nlogn)

https://www.spoj.com/problems/SUBLEX/

*/

#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long lld;

const int N = 1 << 20;

struct suffixarray
{
    char s[N];
    int n, sa[N], r[N], lcp[N], sa2[N], r2[N], c[N], a;
    void init(const char* _s) {
        memset(this, 0, sizeof(suffixarray));
        n = strlen(_s), a = 128;
        memcpy(s, _s, sizeof(char) * n);
        for (int i = 0; i < n; i++) c[r[i] = s[i]]++;
        for (int i = 1; i < a; i++) c[i] += c[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--c[r[i]]] = i;
        for (int l = 1; l < n; l <<= 1) {
            int p = 0;
            for (int i = n - l; i < n; i++) sa2[p++] = i;
            for (int i = 0; i < n; i++) if (sa[i] - l >= 0) sa2[p++] = sa[i] - l;
            for (int i = 0; i < a; i++) c[i] = 0;
            for (int i = 0; i < n; i++) c[r[i]]++;
            for (int i = 1; i < a; i++) c[i] += c[i - 1];
            for (int i = n - 1; i >= 0; i--) sa[--c[r[sa2[i]]]] = sa2[i];
            r2[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                r2[sa[i]] = r2[sa[i - 1]] + 1;
                if (r[sa[i - 1]] == r[sa[i]] && sa[i - 1] + l < n && r[sa[i - 1] + l] == r[sa[i] + l]) r2[sa[i]]--;
            }
            for (int i = 0; i < n; i++) swap(r[i], r2[i]);
            a = r[sa[n - 1]] + 1;
            if (a == n) break;
        }

        for (int i = 0; i < n; i++) r[sa[i]] = i;
        for (int k = 0, i = 0; i < n; i++, k = max(0, k - 1)) {
            if (r[i] == n - 1) {
                lcp[r[i]] = k = 0;
                continue;
            }
            for (int j = sa[r[i] + 1]; max(i, j) + k < n && s[i + k] == s[j + k]; k++);
            lcp[r[i]] = k;
        }
    }
} SA;

int main()
{
    string s;
    cin >> s;
    int n = s.length();
    int Q;
    scanf("%d", &Q);
    vector<pair<int, int>> q(Q);
    for (int i = 0; i < Q; i++)
        scanf("%d", &q[i].first), q[i].second = i;
    vector<pair<int, int>> ans(Q);
    sort(q.rbegin(), q.rend());

    SA.init(s.c_str());

    const int* sa = SA.sa;
    const int* lcp = SA.lcp;

    lld cnt = 0;
    for (int i = 0; i < n; i++)
    {
        cnt += (n - sa[i]) - (i == 0 ? 0 : lcp[i - 1]);
        while (q.size() > 0 && q.back().first <= cnt)
        {
            ans[q.back().second] = { sa[i], n - (cnt - q.back().first) };
            q.pop_back();
        }
    }
    for (int i = 0; i < Q; i++)
        printf("%s\n", s.substr(ans[i].first, ans[i].second - ans[i].first).c_str());
}
