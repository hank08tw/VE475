//implemented by c++ 
#include <iostream>
using namespace std;
long long n=0;
long long e=0;
long long d;
long long plain_text[50];
long long cipher_text[50];
long long extended_euclidean_algorithm(long long a,long long b,long long &x)
{
    long long x0,x1,y0,y1,y;
    x0=1;
    x1=0;  
    y0=0;
    y1=1;
    x=0;
    y=1;
    long long q=(a-a%b)/b;
    while(a%b)
    {
        x=x0-q*x1;
        y=y0-q*y1;
        x0=x1; 
        y0=y1;
        x1=x; 
        y1=y;
        a=b; 
        n=a%b; 
        q=(a-a%b)/b;
    }
    return n;
}
long long transform(long long number[],long long num)
{
    long long i = 0;
    while(num != 0){
        number[i] = num%2;
        num = num/2;
        i++;
    }
    return i;
}
long long modular_expo(long long a, long long b, long long n)
{
    long long c = 0, number[1000];
    long long d = 1;
    long long k = transform(number,b)-1;
    for(long long i = k;i >=0;i--)
    {
        c=c*2;
        d=(d*d)%n;
        if(1==number[i]){
            d=(d*a)%n;
            c++;
        }
    }
    return d;
}




void initialize()
{
    long long prime_number[5000];
    long long cnt = 0, array[1001];
    memset(array, 0, sizeof(array));
    for(long long i = 2; i < 1001; i++)
    if(array[i]==0){
        prime_number[cnt] = i;
        cnt++;
        for(long long j = i*i; j < 1001; j=j+i)
            array[j]=1;
    }
    long long p = prime_number[rand()%cnt], q = prime_number[rand()%cnt];
    n = p*q;
    for(long long j = 3; j < (p-1)*(q-1); j=j+1331)
    {
        long long gcd = extended_euclidean_algorithm(j, (p-1)*(q-1), d);
        if( d>0 && 1==gcd){
            e = j;
            break;
        }

    }
}

void encrypt()
{
    for(long long i = 0; i < 50; i++)cipher_text[i] = modular_expo(plain_text[i], e, n);
}

void decrypt()
{
    for(long long i = 0; i < 50; i++)cipher_text[i] = modular_expo(cipher_text[i], d, n);

}

int main()
{
    srand((unsigned)time(NULL));
    for(long long i = 0; i < 50; i++){plain_text[i] = rand()%1000;}
    while(e!=0)initialize();
    encrypt();
    decrypt();
    return 0;
}