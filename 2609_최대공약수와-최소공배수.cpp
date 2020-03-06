#include <stdio.h>

int gcd(int N, int M)
{
    //first, arrange in decreasing order 
    if(N < M) {
        int t = N;
        N = M;
        M = t;
    }

    //euclidean algorithm
    while(M != 0) {
        int r = N % M;
        N = M;
        M = r;
    }

    return N;
}

int lcm(int N, int M)
{
    int G = gcd(N, M);
    return N * M / G;
}

int main(void)
{
    int N, M;
    scanf("%d %d", &N, &M);

    printf("%d\n", gcd(N, M));
    printf("%d", lcm(N, M));
}