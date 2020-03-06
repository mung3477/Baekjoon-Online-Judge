//DP(memory function) + DFS
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int num;
    int cost;
    int prevs;
    struct node** prev;
} node;

//DP: �� �ǹ� �������� �õ��� ������ �ɸ��� �ð�
int DFS(node** buildings, node* st, int* DP)
{
    node* cur = st;

    //base case
    if(cur->prevs == 0){
        DP[cur->num] = 0;
    }

    //typical case
    //DP table�� ä���� ������ �׳� ������ ��. �� ä���������� ä��. prev�� �߿��� ���� �ɸ��� �ð��� �� ���� ä���Ͽ� DP�� ä��
    else{
        int t = 0, n;

        for(int i = 1; i <= cur->prevs; i++){
            if(DP[cur->prev[i - 1]->num] == -1){
                n = DFS(buildings, buildings[cur->prev[i - 1]->num], DP);
            }
            else{
                n = DP[cur->prev[i - 1]->num] + cur->prev[i - 1]->cost;
            }
            t = (t > n ? t : n);
        }
        DP[cur->num] = t;
    }

    return DP[cur->num] + cur->cost;
}

int main(void)
{
    int T;
    scanf("%d", &T);

    for(int i = 0; i < T; i++){
        //data input phase
        //N: �ǹ��� ���� | K: �Ǽ� ���� ��Ģ�� �� ���� | W: ��ǥ �ǹ�
        int N, K, W;
        int DP[1001] = {-1, };
        for(int i = 1; i <= 1000; i++) DP[i] = -1;

        scanf(" %d %d", &N, &K);
        node** buildings = (node**)malloc(sizeof(node*) * (N + 1));
        buildings[0] = NULL;

        for(int i = 1; i <= N; i++){
            node* newnode = (node*)malloc(sizeof(node));
            newnode->num = i;
            newnode->prev = (node**)malloc(sizeof(node*) * N);
            newnode->prevs = 0;
            scanf(" %d", &newnode->cost);
            buildings[i] = newnode;
        }

        for(int i = 1; i <= K; i++){
            int t1, t2;
            scanf(" %d %d", &t1, &t2);
            buildings[t2]->prev[buildings[t2]->prevs] = buildings[t1];
            (buildings[t2]->prevs)++;
        }

        scanf(" %d", &W);

        //calculating phase
        printf("%d\n", DFS(buildings, buildings[W], DP));
    }

    return 0;
}