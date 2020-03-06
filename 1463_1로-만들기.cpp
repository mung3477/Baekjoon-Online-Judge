#include <cstdio>

int min(int a, int b)
{
    if(a > b) return b;
    else return a;
}

int min_3(int a, int b, int c)
{
    if(min(a, b) > c) return c;
    else return min(a, b);
}

int DP[1000001] = {0, 0, 1, 1, };

int main(void)
{
    int N;
    scanf("%d", &N);

    for(int i = 4; i <= N; i++){
         if(i % 6 == 0){
             DP[i] = min_3(DP[i - 1], DP[i / 3], DP[i / 2]) + 1;
         }
         else if(i % 3 == 0){
             DP[i] = min(DP[i - 1], DP[i / 3]) + 1;
         }
         else if(i % 2 == 0){
             DP[i] = min(DP[i - 1], DP[i / 2]) + 1;
         }
         else DP[i] = DP[i - 1] + 1;
    }
    
    printf("%d", DP[N]);
    return 0;
}