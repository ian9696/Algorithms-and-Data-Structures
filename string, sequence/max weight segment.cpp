/*

max weight segment

Introduction to Algorithms (Fall 2017)
Qualification Problem 4 - Non-empty Segment of Maximum Weight
https://oj.nctu.edu.tw/problems/384/

written by 0310781

*/

#include<stdio.h>

int main(void){
    int n;
    int now=0, m=-10, temp;
    scanf(" %d", &n);
    for(int i=0 ; i<n ; i++){
        scanf(" %d", &temp);
        
        now += temp;
        
        m = m>now?m:now;

        now = (now<0)?0:now;
    }
    printf("%d\n", m);
}
