#include <cstdio>

int DP[100000][3] = {{1, 1, 1}, };

int main(void)
{
    int N;
    scanf("%d", &N);

    for(int i = 1; i <= N - 1; i++){
        DP[i][0] = (DP[i - 1][0] + DP[i - 1][1] + DP[i - 1][2]) % 9901;
        DP[i][1] = (DP[i - 1][0] + DP[i - 1][2]) % 9901;
        DP[i][2] = (DP[i - 1][0] + DP[i - 1][1]) % 9901;
    }

    printf("%d", (DP[N - 1][0] + DP[N - 1][1] + DP[N - 1][2]) % 9901 );
    return 0;
}