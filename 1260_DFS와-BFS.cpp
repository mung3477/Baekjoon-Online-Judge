#include <cstdio>
#include <stack>
#include <queue>
using namespace std;

int adj_mat[1001][1001];

void DFS_call(int V, int N)
{
    stack<int> Stack;
    Stack.push(V);

    int visited[1001] = {0, };
    while(!Stack.empty()){
        int cur = Stack.top();
        if(!visited[cur]){
            printf("%d ", cur);
            visited[cur] = 1;
        }
        Stack.pop();

        for(int i = N; i >= 1; i--){
            if(adj_mat[cur][i] && !visited[i]){
                Stack.push(i);
             }
        }
    }
}

void BFS_call(int V, int N)
{
    queue<int> Queue;
    Queue.push(V);

    int visited[1001] = {0, };
    while(!Queue.empty()){
        int cur = Queue.front();
        if(!visited[cur]){
            printf("%d ", cur);
            visited[cur] = 1;
        }
        Queue.pop();

        for(int i = 1; i <= N; i++){
            if(adj_mat[cur][i] && !visited[i]){
                Queue.push(i);
            }
        }
    }
}

int main(void)
{
    int N, M, V;
    scanf("%d %d %d", &N, &M, &V);

    for(int i = 1; i <= M; i++){
        int from, to;
        scanf(" %d %d", &from, &to);
        adj_mat[from][to] = 1;
        adj_mat[to][from] = 1;
    }

    DFS_call(V, N);
    printf("\n");
    BFS_call(V, N);

    return 0;
}