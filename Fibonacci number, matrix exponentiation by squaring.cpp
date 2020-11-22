/*

Fibonacci number, matrix exponentiation by squaring

O(log(n))

Introduction to Algorithms (Fall 2017)
homework1. Fibonacci Numbers in O(log n) time
https://oj.nctu.edu.tw/problems/208/

*/

#include<cstdio>
#include<cstring>

const int P=29989;
const int L=2;

struct Mat
{
    int a[2][2];
    Mat(int ind=0)
    {
        memset(a, 0, sizeof(a));
        if(ind)
            for(int i=0; i<L; i++)
                a[i][i]=1;
    }
    Mat operator*(const Mat& r)
    {
        Mat res;
        for(int i=0; i<L; i++)
            for(int j=0; j<L; j++)
                for(int k=0; k<L; k++)
                    res.a[i][j]=(res.a[i][j]+a[i][k]*r.a[k][j])%P;
        return res;
    }
    Mat operator^(int p)
    {
        Mat res(1), tmp=*this;
        for(; p>0; tmp=tmp*tmp, p/=2)
            if(p%2)
                res=res*tmp;
        return res;
    }
};

int main()
{
    int T;
    for(scanf("%d", &T); T>0; T--)
    {
        int n;
        scanf("%d", &n);
        if(n<=2)
        {
            printf("1\n");
            continue;
        }
        Mat mat;
        mat.a[0][1]=mat.a[1][0]=mat.a[1][1]=1;
        mat=mat^(n-1);
        printf("%d%s", ((mat.a[0][0]+mat.a[0][1])%P), T==1?"":"\n");
    }
}
