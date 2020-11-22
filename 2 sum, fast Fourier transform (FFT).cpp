/*

2 sum, fast Fourier transform (FFT)

Competitive Programming 1 (Spring 2018)
Assignment 8 (Week 6) - Summands
https://oj.nctu.edu.tw/problems/479/

*/

#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<complex>
#include<cstring>
using namespace std;

typedef long long lld;
typedef complex<double> cplx;

const double PI=acos(0)*2;
const int N=16;
cplx a[1<<(N+1)], b[1<<(N+1)];
int cnt[1<<N];
lld ans[1<<(N+1)];

void fft(cplx A[], int lgn, bool inv=false){
	int n=1<<lgn;
	for(int i=0, j=1; j<n-1; j++){
		for(int k=n>>1; k>(i^=k); k>>=1);
		if( j<i ) swap(A[i], A[j]);
	}
	for(int i=1; i<n; i<<=1){
		cplx W(1, 0), Wn(cos(PI/i), sin((inv ? -PI : PI)/i));
		for(int j=0; j<n; j++){
			if( j&i ){
				W=cplx(1, 0); continue;
			}
			cplx x=A[j], y=A[j+i]*W;
			A[j]=x+y; A[j+i]=x-y;
			W*=Wn;
		}
	}
	if( inv ) for(int i=0; i<n; i++) A[i]/=n;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i=0, t; i<n; i++)
    {
        scanf("%d", &t);
        cnt[t]++;
    }
    for(int i=0; i<1<<N; i++)
        a[i]=b[i]=cnt[i];
    fft(a, N+1);
    fft(b, N+1);
    for(int i=0; i<1<<(N+1); i++)
        a[i]*=b[i];
    fft(a, N+1, true);
    for(int i=0; i<1<<N; i++)
        a[i<<1]-=cnt[i];
    for(int i=0; i<1<<(N+1); i++)
        ans[i]=round(a[i].real()/2);

    for(int t; m>0; m--)
    {
        scanf("%d", &t);
        printf("%lld\n", ans[t]);
    }
}
