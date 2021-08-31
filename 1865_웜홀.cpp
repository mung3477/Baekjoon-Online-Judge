#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
using std::fill;

int main()
{
    int TC, N, M, W, S, E, T;
    bool able;
    int** adjMat;
    
    cin >> TC;
    for (TC; TC > 0; TC--) {
        cin >> N >> M >> W;
        
        able = false;
        
        //가장 작은 cost의 간선만 저장하는 인접 행렬
        adjMat = new int*[N + 1];
        for (int i = 0; i <= N; i++) {
            adjMat[i] = new int[N + 1];
            fill(adjMat[i], &adjMat[i][N + 1], 10001);
        }
        
        //양방향 간선은 돌아오는 path를 구할 때도 쓰임. cost는 항상 양수.
        for (int i = 0; i < M; i++) {
            cin >> S >> E >> T;
            
            //둘 사이에 간선이 아직 없거나, 이 간선이 더 cost가 작은 경우 그 간선을 cycle 탐색용 matrix에 저장.
            //여기까지는 양방향 간선 밖에 없으므로, 한 쪽만 탐색해봐도 존재 여부를 확인하는데는 무관.
            if (adjMat[S][E] == 10001 || (adjMat[S][E] != 10001 && T < adjMat[S][E])) {
                adjMat[S][E] = T;
                adjMat[E][S] = T;
            }
        }
        
        //웜홀도 가장 작은 cost만 저장.
        for (int i = 0; i < W; i++) {
            cin >> S >> E >> T;
            T = -T;
            
            if (adjMat[S][E] == 10001 || (adjMat[S][E] != 10001 && T < adjMat[S][E])) {
                adjMat[S][E] = T;
            }
        }
        
        //floyd Warhsall
        for (int k = 1; k <= N; k++) {
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    int newPathCost = adjMat[i][k] + adjMat[k][j];
                    if (newPathCost < adjMat[i][j]) {
                        adjMat[i][j] = newPathCost;
                    }
                }
            }
        }
        
        for (int i = 1; i <= N && !able; i++) {
            for (int j = 1; j <= N && !able; j++) {
                if (adjMat[i][j] + adjMat[j][i] < 0) {
                    cout << "YES\n";
                    able = true;
                }
            }
        }
        
        if (!able) {
            cout << "NO\n";
        }
        
        for (int i = 0; i <= N; i++) {
            delete[] adjMat[i];
        }    
        delete[] adjMat;
    }
   
   return 0;
}
