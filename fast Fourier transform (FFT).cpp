/*

fast Fourier transform (FFT)

2016-2017 ACM-ICPC, South Pacific Regional Contest (SPPC 16)
problem C - Crazy Rotations
http://codeforces.com/gym/101177

*/

#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1 << 19;
const double PI = acos(-1.0);
struct vir {
	double re, im;
	vir(double _re = 0, double _im = 0) :re(_re), im(_im) {}
};
vir operator +(vir a, vir b) { return vir(a.re + b.re, a.im + b.im); }
vir operator -(vir a, vir b) { return vir(a.re - b.re, a.im - b.im); }
vir operator *(vir a, vir b) { return vir(a.re*b.re - a.im*b.im, a.re*b.im + a.im*b.re); }
vir x1[2 * N], x2[2 * N];

int rev(int x, int len) {
	int r = 0, i;
	for (i = 0; i < len; i++, x >>= 1) r = (r << 1) + (x & 1);
	return r;
}
void change(vir *x, int len, int loglen) {
	for (int i = 0; i < len; i++)
		if (rev(i, loglen) < i) swap(x[rev(i, loglen)], x[i]);
}
void fft(vir *x, int len, int loglen) {
	change(x, len, loglen);
	int i, j, s, t = 1;
	for (i = 0; i < loglen; i++, t <<= 1) {
		for (s = 0; s < len; s += t + t) {
			vir a, b, wo(cos(PI / t), sin(PI / t)), wn(1, 0);
			for (j = s; j < s + t; j++) {
				a = x[j]; b = x[j + t] * wn;
				x[j] = a + b; x[j + t] = a - b;
				wn = wn*wo;
			}
		}
	}
}
void dit_fft(vir *x, int len, int loglen) {
	int i, j, s, t = len >> 1;
	for (i = 0; i < loglen; i++, t >>= 1) {
		for (s = 0; s < len; s += t + t) {
			vir a, b, wn(1, 0), wo(cos(PI / t), -sin(PI / t));
			for (j = s; j < s + t; j++) {
				a = x[j] + x[j + t]; b = (x[j] - x[j + t])*wn;
				x[j] = a; x[j + t] = b;
				wn = wn*wo;
			}
		}
	}
	change(x, len, loglen);
	for (i = 0; i < len; i++) x[i].re /= len;
}

const int L = 500000;
char s[L + 2];
int cnt[L + 2];
char *str = "BYR";

int main()
{
	int n, p;
	scanf("%d%d", &n, &p);
	scanf("%s", s);
	int len = 1, loglen = 0;
	while (len <= 2 * n + 5)
	{
		len *= 2;
		loglen++;
	}
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < len; i++)
			x1[i] = x2[i] = 0;
		for (int i = 0; i < n; i++)
		{
			if (s[i] != str[k])
				x1[i] = 1;
			if (s[n - 1 - i] == str[k])
				x2[i] = 1;
		}
		fft(x1, len, loglen);
		fft(x2, len, loglen);
		for (int i = 0; i < len; i++)
			x1[i] = x1[i] * x2[i];
		dit_fft(x1, len, loglen);
		for (int i = n - 2, j = 1; i >= 0; i--, j++)
			cnt[j] += (int)round(x1[i].re);
		for (int i = 2 * n - 2, j = 1; i >= n; i--, j++)
			cnt[j] += (int)round(x1[i].re);
	}
	vector<pair<int, int>> v;
	for (int i = 1; i < n; i++)
		v.push_back({ cnt[i], i });
	sort(v.begin(), v.end());
	//for (auto &pa : v)
	//printf("shift=%d   cnt=%d\n", pa.second, pa.first);
	int ans = n;
	for (auto &pa : v)
		if (pa.first == v[p - 1].first)
			ans = min(ans, pa.second);
	printf("%d\n", ans);
}
