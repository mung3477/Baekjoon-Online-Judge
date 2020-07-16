#include <cstdio>
#include <string.h>

/*
가장 간단하게 했을 때 max cal: (50 * 50 * 2) * (49 * 49) * 2 < 1초

매 swap 마다 최대 개수 체크.

swapNcheck: swap -> 전체 배열 돌면서 max count
*/

int swapNcheck(char** mat, int r1, int r2, int c1, int c2, int N);
int max_2(int a, int b);
////////////////////////////////////////////////

int main(void)
{
    int N;
    scanf(" %d", &N);
    
    char** mat;
    mat = new char*[N];
    for(int i = 0; i < N; i++){
        mat[i] = new char[N];
        memset(mat[i], '\0', sizeof(char) * N);
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf(" %c", &mat[i][j]);
        }
    }

    int max = 0, temp;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N - 1; j++){
            temp = swapNcheck(mat, i, i, j, j + 1, N); //좌우
            max = max_2(max, temp);

            if(i != N - 1){
                temp = swapNcheck(mat, i, i + 1, j, j, N); //상하
                max = max_2(max, temp);
            }
        }
    }
    
    
    printf("%d", max);
    return 0;
}

int swapNcheck(char** mat, int r1, int r2, int c1, int c2, int N)
{
    if(mat[r1][c1] != mat[r2][c2]){
        //swap
        char t = mat[r1][c1];
        mat[r1][c1] = mat[r2][c2];
        mat[r2][c2] = t;

        //check
        int maxCount = 0;

        //horizontal 
        for(int i = 0; i < N; i++){

            char curWord = mat[i][0];
            int curCount = 1;

            for(int j = 1; j < N; j++){
                if(mat[i][j] == curWord) {
                    curCount++;
                }
                else {
                    if(maxCount < curCount){
                        maxCount = curCount;
                    }
                    curWord = mat[i][j];
                    curCount = 1;
                }
            }

            if(maxCount < curCount){
                maxCount = curCount;
            }
        }

        //vertical
        for(int i = 0; i < N; i++){

            char curWord = mat[0][i];
            int curCount = 1;

            for(int j = 1; j < N; j++){
                if(mat[j][i] == mat[j - 1][i]) {
                    curCount++;
                }
                else {
                    if(maxCount < curCount){
                        maxCount = curCount;
                    }
                    curWord = mat[j][i];
                    curCount = 1;
                }
            }

            if(maxCount < curCount){
                maxCount = curCount;
            }
        }

        //swap remove
        t = mat[r1][c1];
        mat[r1][c1] = mat[r2][c2];
        mat[r2][c2] = t;

        return maxCount;
    }
    else return 0;
}

int max_2(int a, int b)
{
    if(a > b) return a;
    else return b;
}