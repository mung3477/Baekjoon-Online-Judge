#include <cstdio>
#include <cmath>

double expect[7][7][7][1001];

double max(double a, double b)
{
    if(a > b) return a;
    else return b;
}

int max_3(int a, int b, int c)
{
    if(max(a, b) > c) return max(a, b);
    else return c;
}

int prize(int i, int j, int k)
{
    if(i == j){
        if(j == k){
            return 10000 + i * 1000;
        }
        else{
            return 1000 + i * 100;
        }
    }

    else{
        if(j == k){
            return 1000 + j * 100;
        }
        else if(j != k && k == i){
            return 1000 + i * 100;
        }
        else{
            return max_3(i, j ,k) * 100;
        }
    }
}

double dice(int i, int j, int k, int cur, int N)
{
    double curPrize = (double)prize(i, j, k);

    if(cur == N) return curPrize;

    double& curBest = expect[i][j][k][cur];
    if(curBest) return curBest;

    double next = 0;
    for(int s = 1; s <= 6; s++){
        next += dice(j, k, s, cur + 1, N);
    }

    return curBest = max(next / 6, curPrize);
}

int main(void)
{
    int N;
    scanf("%d", &N);

    double ans = 0;
    int cur = 3;

    for(int i = 1; i <= 6; i++){
        for(int j = 1; j <= 6; j++){
            for(int k = 1; k <= 6; k++){
                ans += dice(i, j, k, 3, N);
            }
        }
    }

    printf("%lf", ans / (6 * 6 * 6));
}