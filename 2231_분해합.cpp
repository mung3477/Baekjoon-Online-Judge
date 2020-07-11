#include <cstdio>

/*
분해합이 N인 제일 작은 M 찾기.
N의 생성자 : N ~ N - 9 * 자리수 중 하나.
자리수가 1 ~ 7 이니까 63개만 보면 됨. brute force!
*/


//////////////////////////////////////////////////
int decomp_sum(int K);
int digit(int N);

//////////////////////////////////////////////////
int main(void)
{
    int N, M, K;
    scanf(" %d", &N);
    
    K = N - 9 * digit(N);
    for(K; K <= N; K++){
        if(decomp_sum(K) == N) break;
    }
    if(K == N + 1) {
        printf("0");
    }
    else{
        printf("%d", K);
    }
    return 0;
}

int digit(int N)
{
    int digit = 0;
    for(N; N; N /= 10){
        digit++;
    }
    return digit;
}

int decomp_sum(int K)
{
    int decomp_sum = K;
    for(K; K; K /= 10){
        decomp_sum += K % 10;
    }
    return decomp_sum;
}