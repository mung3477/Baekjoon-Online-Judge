#include <iostream>
#include <math.h>
using std::cin;
using std::cout;

int N, allUsed;
int** adjMat;   //0 ~ N-1
int** minCostMadeWith;   //bitmask index v15 v14 ... v0, End. 쓴 정점들이 주어졌을 때 남은 정점들로 만들어낼 수 있는 path 중 최소 cost

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

//쓴 정점들이 주어졌을 때 남은 정점들로 만들어낼 수 있는, end를 시작으로 하는 path 중 최소 cost를 return
int minPathCost(int used, int end) {
    //terminate 
    if (used == allUsed) {
        //cycle
        if (adjMat[end][0]) return adjMat[end][0];
        //can't return to the start
        else return 17000000;
    }
    
    //use memoization
    if (minCostMadeWith[used][end]) return minCostMadeWith[used][end];
    
    int next, retVal = 17000000;   //use vi additionally
    
    for (int i = 1; i < N; i++) {
        //현재 경로의 뒤에 i가 붙을 수 있을 때 && i가 아직 쓰이지 않은 정점일때
        next = used | 1 << i;
        if (adjMat[end][i] && next != used) {
            //memoize
            minCostMadeWith[next][i] = minPathCost(next, i);
            retVal = min(retVal, adjMat[end][i] + minCostMadeWith[next][i]);
        }
    }
    
    return retVal;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    
    allUsed = (1 << N) - 1;
    minCostMadeWith = new int*[allUsed + 1];
    for (int i = 0; i <= allUsed; i++) {
        minCostMadeWith[i] = new int[N + 1]{};
    }
    
    adjMat = new int*[N + 1];
    for (int i = 0; i < N; i++) {
        adjMat[i] = new int[N]{};
        for (int j = 0; j < N; j++) {
            cin >> adjMat[i][j];
        }
    }
    
    cout << minPathCost(1, 0);
    
    return 0;
}
