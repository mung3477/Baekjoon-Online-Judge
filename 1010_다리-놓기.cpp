#include <stdio.h>
//mCn

unsigned long long down_fact(int M, int A)
{
    unsigned long long ans = 1;
    for(int i = M; i > A; i--){
        ans *= i;
    }
    return ans;
}

int main(void)
{
    int T;
    scanf("%d", &T);
    unsigned long long factorial[30] = {1, 1, };

    for(int i = 2; i <= 29; i++){
        factorial[i] = factorial[i - 1] * i;
    }

    for(int i = 1; i <= T; i++){
        int N, M;
        scanf(" %d %d", &N, &M);

        int A = (N > M - N ? N : M - N);
        int B = (A == N ? M - N : N);

        unsigned long long ans = down_fact(M, A) / factorial[B];
        printf("%llu\n", ans);
    }
}