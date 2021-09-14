#include <iostream>
using std::cin;
using std::cout;

int min(int a, int b) {
    if (a > b) return b;
    else return a;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M, from, to, cost, newPathCost;
    int** adjMat;
    
    cin >> N >> M;
    adjMat = new int*[N + 1];
    for (int i = 1; i <= N; i++) {
        adjMat[i] = new int[N + 1]{};
    }
    
    for (M; M > 0; M--) {
        cin >> from >> to >> cost;
        if (adjMat[from][to]) {
            adjMat[from][to] = min(adjMat[from][to], cost);
        }
        else adjMat[from][to] = cost;
    }
    
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i != j && adjMat[i][k] && adjMat[k][j]) {
                    newPathCost = adjMat[i][k] + adjMat[k][j];
                    
                    if (adjMat[i][j]) {
                        adjMat[i][j] = min(adjMat[i][j], newPathCost); 
                    }
                    else adjMat[i][j] = newPathCost;
                }
            }
        }
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << adjMat[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
