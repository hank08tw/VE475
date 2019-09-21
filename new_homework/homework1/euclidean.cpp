#include <stdio.h>
#include <iostream>
using namespace std;

int main(){
    unsigned long a,b,r1,r0,tmp,tmp1,tmp2,tmp3;
    long s1,s0,t1,t0;
    printf("input number a: ");
    scanf("%lu",&a);
    printf("input number b: ");
    scanf("%lu",&b);

    
    r0=b;
    r1=a;
    s0=0;
    s1=1;
    t0=1;
    t1=0;
     
    while(r0!=0){
        tmp=r1/r0;
        tmp1=r1-tmp*r0;
        r1=r0;
        r0=tmp1;
        tmp2=s1-tmp*s0;
        s1=s0;
        s0=tmp2;
        tmp3=t1-tmp*t0;
        t1=t0;
        t0=tmp3;

    }
    printf("gcd(a,b) is: %lu\n",r1);
    printf("ax+by=1, x and y are: %lu %lu\n",s1,t1);
    return 0;
}