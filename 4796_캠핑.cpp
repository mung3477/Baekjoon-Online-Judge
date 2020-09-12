#include <cstdio>

int min_2(int a, int b){
    if(a > b) return b;
    else return a;
}

int main(void)
{
    int rep = 1;
    while(rep){
        int L, P, V;
        scanf(" %d %d %d", &L, &P, &V);
        if(L && P && V){
            int ans;
            int Q = V / P;
            int R = V % P;
            
            ans = Q * L + min_2(L, R);
            printf("Case %d: %d\n", rep, ans);
            rep++;
        }

        else return 0;
    }
}