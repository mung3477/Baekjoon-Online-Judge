#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

int adj_mat[1001][1001];
int path[1000000];

bool euiler(int cur, int N, int M)
{
    if(cur + 1 == M + 1){
        for(int i = 0; i <= cur; i++){
            printf("%d ", path[i]);
        }
        return true;
    }
    
    for(int i = 1; i <= N; i++){
        if(adj_mat[path[cur]][i]){
            adj_mat[path[cur]][i]--;
            adj_mat[i][path[cur]]--;
            path[cur + 1] = i;
            if(euiler(cur + 1, N, M)) return true;
            else{
                adj_mat[path[cur]][i]++;
                adj_mat[i][path[cur]]++;
            }
        }
    }

    return false;
}

void euiler_call(int N, int M)
{
    path[0] = 1;
    if(!euiler(0, N, M)){
        printf("-1");
    }
    return;
}

int main(void)
{
    int N, M = 0;
    scanf("%d", &N);

    int t;
    bool able = true;

    for(int i = 1; i <= N; i++){
        int e = 0;
        for(int j = 1; j <= N; j++){
            scanf(" %d", &t);
            
            if(t){
                if(i < j) M += t;
                e += t;
                adj_mat[i][j] = t;
            }
        }

        if(e % 2) able = false;
    }

    if(!able) {
        printf("-1");
        return 0;
    }

    euiler_call(N, M);
    return 0;
}