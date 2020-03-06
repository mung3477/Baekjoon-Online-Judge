#include <stdio.h>

void inverse(int A[51][51], int i, int j)
{
    for(int t = i; t <= i + 2; t++){
        for(int k = j; k <= j + 2; k++){
            A[t][k] = !A[t][k];
        }
    }
}

bool compare(int A[51][51], int B[51][51], int N, int M)
{
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            if(A[i][j] != B[i][j]) return false;
        }
    }
    return true;
}

void printA(int A[51][51], int N, int M)
{
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            printf("%d", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    int N, M;
    scanf("%d %d", &N, &M);
    getchar();

    int A[51][51];
    int B[51][51];

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            A[i][j] = getchar() - '0';
        }
        getchar();
    }

    
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            B[i][j] = getchar() - '0';
        }
        getchar();
    }

    if((N < 3 || M < 3) && !compare(A, B, N, M)) {
        printf("-1");
        return 0;
    }

    else if(compare(A, B, N, M)) {
        printf("0");
        return 0;
    }

    int count = 0;
    
    for(int i = 1; i <= N - 2; i++){
        for(int j = 1; j <= M - 2; j++){
            if(A[i][j] != B[i][j]) {
                inverse(A, i , j);
                count++;
                //printA(A, N, M);
            }
        }
    }

    if(compare(A, B, N, M)) printf("%d", count);
    else printf("-1");
    return 0;
}