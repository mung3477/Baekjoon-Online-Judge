#include <stdio.h>
using namespace std;

bool usable(int i ,int level,int used[])
{
    for(int j = 0; j < level; j++) {
        if(i == used[j]) return false;
    }

    return true;
}

void DFS(int N, int M, int level, int used[])
{
    //base case
    if(level == M) {
        for(int k = 0; k < level; k++) {
            printf("%d ", used[k]);
        }
        printf("\n");
        return;
    }

    //normal case
    //1. find usable number
    for(int i = 1; i <= N; i++) {
        if(usable(i, level, used)) {
            used[level] = i;
            DFS(N, M, level + 1, used);
        }
    }
    return;
}

int main(void)
{
    //1부터 N까지 M개를 고른다.
    int N, M;
    scanf("%d %d", &N, &M);

    int used[8];
    for(int i = 0; i < 8; i++) {
        used[i] = -1;
    }

    DFS(N, M, 0, used);
}