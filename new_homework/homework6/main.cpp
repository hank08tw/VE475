//implement Pollard’s Rho Algorithm in C++
#include <iostream>
using namespace std;
long long f(long long first, long long n)
{
    long long tmp=first*first+1;
    tmp=tmp%n;
    return tmp;
}
long long gcd(long long first, long long second)
{
    if(second==0)return first;
    return gcd(second, first%second);
}

int main()
{
    long long n;
    cout << "input number n:" << endl;
    cin >> n;
    cout << n << "=";
    if (n>=2){
        while (1){
            long long first = 2;
            long long second = 2;
            long long third = 1;
            while (third == 1){
                first = f(first, n);
                long long tmp=f(second, n);
                second = f(tmp, n);
                if (first>second){
                    third = gcd(first-second, n);
                }else{
                    third = gcd(second-first, n);
                }
            }
            if (n==third){
                cout << third;
                break;
            } else{
                cout << third << "x";
                n /= third;
            }
        }
    }
    cout << endl;
    return 0;
}