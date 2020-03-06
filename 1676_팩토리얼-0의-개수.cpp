#include <cstdio>

int F[10000000] = {0, 1, };

void rearrange(int* num, int& dig)
{
    for(int i = 1; i <= dig; i++){
        int loop = 1, t = num[i];
        num[i] = t % 10;
        t /= 10;

        while(t){
            num[i + loop] += t % 10;
            t /= 10;
            loop++;
        }
        if(i == dig) dig += loop - 1;
    }
}

//자리수 반환. m을 곱함
void multiply(int* num, int m, int& dig)
{
    for(int i = 1; i <= dig; i++){
        num[i] *= m;
    }
    
    rearrange(num, dig);
}

int main(void)
{
    int N;
    scanf("%d", &N);

    int dig = 1;
    for(int i = 2; i <= N; i++){
        multiply(F, i, dig);
    }

    int ans = 0;
    while(!F[ans + 1]) ans++;
    printf("%d", ans);
    
    return 0;
}