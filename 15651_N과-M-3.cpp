#include <stdio.h>

void DFS(int N, int M, int last, int used[]) 
{
    //base case
    if(last == M) {
        for(int i = 0; i < last; i++) {
            printf("%d ", used[i]);
        }
        printf("\n");
        return;
    }

    //typical case
    for(int i = 1; i <= N; i++) {
        used[last] = i;
        DFS(N, M, last + 1, used);
    }
}

int main(void)
{
    int N, M;
    scanf("%d %d", &N, &M);

    int used[7];

    DFS(N, M, 0, used);
}