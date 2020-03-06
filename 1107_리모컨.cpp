#include <stdio.h>
#include <math.h>

//If all buttons composing the number are usable, then make flag false and return -1. Else, return the digit which can't be pressed using remote controller.
int movable(int i, int* broken, int M, bool* flag)
{
    int broke = 0;
    if(i == 0 && broken[i]) return broke;

    for(i; i; i /= 10, broke++){
        if(broken[i % 10]){
            return broke;
        }
    }
    *flag = false;
    return -1;
}

//count the digit of given number
int digit(int i)
{   
    int dig = 0;
    for(i; i; i /= 10){
        dig++;
    }
    return dig;
}

int main(void)
{
    //while(1){

    int N, M, t;
    int broken[10] = { 0, };

    scanf("%d", &N);
    scanf(" %d", &M);
    for(int i = 0; i < M; i++){
        scanf(" %d", &t);
        broken[t] = 1;
    }

    int ans = abs(N - 100);

    //리모컨으로 다른 채널 이동 가능
    if(M != 10){
        int i = N, k;
        bool flag = true;
        for(i; flag && i <= 999900; ){
            k = movable(i, broken, M, &flag); 
            if(flag){
                i += (int)pow(10, k);
                i -= i % (int)pow(10, k);
            }
        }
        
        if(i <= 999900){
            int to_bigger;
            if(i == 0) to_bigger = 1 + abs(i - N);
            else to_bigger = digit(i) + abs(i - N);
            ans = (ans > to_bigger ? to_bigger : ans);
        }

        flag = true;
        for(i = N; flag && i >= 0; ){
            k = movable(i, broken, M, &flag);
            if(flag){
                i -= (int)pow(10 , k);
                i = i - i % (int)pow(10, k) + (int)pow(10, k) - 1;
            }
        }

        if(i >= 0){
            int to_lower;
            if(i == 0){
                to_lower = 1 + abs(N - i);
            }
            else{
                to_lower = digit(i) + abs(N - i);
            }
            ans = (ans > to_lower ? to_lower : ans);
        }
    }
    printf("%d", ans);
    //}
    return 0;
}