#include <iostream>
#include <limits.h>
using std::cin;
using std::cout;



int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int min3(int a, int b, int c) {
    int minAB = min(a, b);
    if (minAB < c) return minAB;
    else return c;
}

int min4(int a, int b, int c, int d) {
    int minABC = min3(a, b, c);
    if (minABC < d) return minABC;
    else return d;
}

void fillDP_0(int** DP, int** Enemy, const int& i, const int& W) {
    DP[i][0] = min(DP[i - 1][2] + 1, (Enemy[0][i - 1] + Enemy[0][i] <= W ? DP[i - 1][1] + 1 : INT_MAX));
}

void fillDP_1(int** DP, int** Enemy, const int& i, const int& W) {
    DP[i][1] = min(DP[i - 1][2] + 1, (Enemy[1][i - 1] + Enemy[1][i] <= W ? DP[i - 1][0] + 1 : INT_MAX));
}

void fillDP_2(int** DP, int** Enemy, const int& i, const int& W) {
    DP[i][2] = min4(DP[i][0] + 1, DP[i][1] + 1, 
                        (Enemy[0][i] + Enemy[1][i] <= W ? DP[i - 1][2] + 1 : INT_MAX),
                        (Enemy[0][i - 1] + Enemy[0][i] <= W && Enemy[1][i - 1] + Enemy[1][i] <= W ? DP[i - 2][2] + 2 : INT_MAX)
                );
}

void fillDP(int** DP, int** Enemy, int i, const int& END, const int& W) {
    for (i; i <= END; i++) {
        fillDP_0(DP, Enemy, i, W);
        fillDP_1(DP, Enemy, i, W);
        fillDP_2(DP, Enemy, i, W);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int T;
    cin >> T;
    for (T; T > 0; T--) {
        int N, W;
        cin >> N >> W;
        
        int** Enemy;
        int** DP;
        int ans = INT_MAX;
        
        Enemy = new int*[2];
        for (int i = 0; i < 2; i++) 
            Enemy[i] = new int[N + 1]{};
        
        DP = new int*[N + 1];
        for (int i = 0; i <= N; i++) 
            DP[i] = new int[3]{};
        
        for (int i = 0; i < 2; i++) {
            for (int j = 1; j <= N; j++) {
                cin >> Enemy[i][j];
            }
        }
        
        if (N == 1) {
            ans = (Enemy[0][1] + Enemy[1][1] <= W ? 1 : 2);
        }
        
        else {
            //1열과 N열이 묶이지 않음
            DP[0][0] = DP[0][1] = DP[0][2] = 0;
            DP[1][0] = 1; DP[1][1] = 1; DP[1][2] = (Enemy[0][1] + Enemy[1][1] <= W ? 1 : 2);
            fillDP(DP, Enemy, 2, N, W);
            ans = min(ans, DP[N][2]);
            
            //1열과 N열의 0행이 묶이는 경우
            if (Enemy[0][1] + Enemy[0][N] <= W) {
                DP[1][0] = 0; DP[1][1] = 1; DP[1][2] = 1;
                
                DP[2][0] = DP[1][2] + 1;
                fillDP_1(DP, Enemy, 2, W);
                DP[2][2] = min3(DP[2][0] + 1, DP[2][1] + 1, (Enemy[0][2] + Enemy[1][2] <= W ? DP[1][2] + 1 : INT_MAX));
                
                fillDP(DP, Enemy, 3, N - 1, W);
                
                if (N > 2) fillDP_1(DP, Enemy, N, W);
                ans = min(ans, DP[N][1] + 1);
            }
            
            //1열과 N열의 1행이 묶이는 경우
            if (Enemy[1][1] + Enemy[1][N] <= W) {
                DP[1][0] = 1; DP[1][1] = 0; DP[1][2] = 1;
                
                fillDP_0(DP, Enemy, 2, W);
                DP[2][1] = DP[1][2] + 1;
                DP[2][2] = min3(DP[2][0] + 1, DP[2][1] + 1, (Enemy[0][2] + Enemy[1][2] <= W ? DP[1][2] + 1 : INT_MAX));
                fillDP(DP, Enemy, 3, N - 1, W);
                
                if (N > 2) fillDP_0(DP, Enemy, N, W);
                ans = min(ans, DP[N][0] + 1);
            }
            
            //1열과 N열의 0행 1행 모두 묶이는 경우
            if ((Enemy[0][1] + Enemy[0][N] <= W) && (Enemy[1][1] + Enemy[1][N] <= W)) {
                DP[1][0] = DP[1][1] = DP[1][2] = 0;
                
                DP[2][0] = 1; DP[2][1] = 1; DP[2][2] = (Enemy[0][2] + Enemy[1][2] <= W ? 1 : 2);
                fillDP(DP, Enemy, 3, N - 1, W);
                
                ans = min(ans, DP[N - 1][2] + 2);
            }
        }
        
        cout << ans << "\n";
        
        
        for (int i = 0; i <= N; i++) 
            delete[] DP[i];
        delete[] Enemy[0], Enemy[1], Enemy, DP;
        
    }
    
    return 0;
}
