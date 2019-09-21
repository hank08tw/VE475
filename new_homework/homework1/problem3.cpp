#include <iostream>
#include <time.h>
#include <ctime>

#include <gmpxx.h>
using namespace std;
mpz_class extended_euclidean(mpz_class first_num,mpz_class second_num){
    mpz_class r1,r0,tmp,tmp1,tmp2,tmp3,s1,s0,t1,t0;
    r0=second_num;
    r1=first_num;
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
    return r1;
}
int main(){
    gmp_randclass randclass(gmp_randinit_default);
    randclass.seed(time(0));
    mpz_class first_num = randclass.get_z_bits(4096);
    mpz_class second_num = randclass.get_z_bits(4096);
    mpz_class gmpfunctionresult = gcd(first_num, second_num);
    mpz_class myresult=extended_euclidean(first_num,second_num);
    cout << "The first integar is " << first_num << endl;
    cout << "The second integar is " << second_num << endl;
    cout << "gcd(a,b) result with own implemented extended euclidean algorithm is " << myresult << endl;
    cout << "gcd(a,b) result with gmp function in gmp library is " << gmpfunctionresult << endl;
    

    if (myresult==gmpfunctionresult){cout << "Results are same" << endl;}
    else {cout << "Results are different" << endl;}

    return 0;
}
