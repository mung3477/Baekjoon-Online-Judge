#include <cstdio>

int cost[1001][3];

int min(int a, int b)
{
    if(a >= b) return b;
    else return a;
}

int min_3(int a, int b, int c)
{
    if(min(a, b) >= c) return c;
    else return min(a, b);
}

int main(void)
{
    int N;
    scanf("%d", &N);


    int R[1000] = {0, }, B[1000] = {0, }, G[1000] = {0, };
    for(int i = 0; i <= N - 1; i++){
        scanf(" %d %d %d", &R[i], &G[i], &B[i]);
    }

    cost[0][0] = R[0];
    cost[0][1] = G[0];
    cost[0][2] = B[0];


    for(int i = 1; i <= N - 1; i++){
        cost[i][0] = R[i] + min(cost[i - 1][1], cost[i - 1][2]);
        cost[i][1] = G[i] + min(cost[i - 1][0], cost[i - 1][2]);
        cost[i][2] = B[i] + min(cost[i - 1][0], cost[i - 1][1]);
    }

    printf("%d", min_3(cost[N - 1][0], cost[N - 1][1], cost[N - 1][2]));
    
    return 0;
}