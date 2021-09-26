#include <iostream>
using std::cin;
using std::cout;

struct method {
    int R;
    int D;
    int RD;
    method(): R(0), D(0), RD(0) {};
    method(int R, int D, int RD): R(R), D(D), RD(RD) {};
    
    int sum() {
        return R + D + RD;
    }
};

bool** map;
method** DP;
int N;

void fillDP(int i, int j){
    if (!map[i][j]) {
        DP[i][j].R = (!map[i][j - 1] ? DP[i][j - 1].R + DP[i][j - 1].RD : 0);
        DP[i][j].D = (!map[i - 1][j] ? DP[i - 1][j].D + DP[i - 1][j].RD : 0);
        DP[i][j].RD = (!map[i][j - 1] && !map[i - 1][j] ? DP[i - 1][j - 1].R + DP[i - 1][j - 1].D + DP[i - 1][j - 1].RD : 0);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    
    //construct
    map = new bool*[N + 1];
    DP = new method*[N + 1];
    for (int i = 0; i <= N; i++) {
        map[i] = new bool[N + 1]{};
        DP[i] = new method[N + 1]{};
    }
    //initialize
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i <= N; i++) {
        map[i][0] = 1;
        map[0][i] = 1;
        
        DP[i][0] = method();
        DP[0][i] = method();
    }
    
    DP[1][1] = method();
    DP[1][2] = method(1, 0, 0);
    
    for (int j = 3; j <= N; j++) {
        fillDP(1, j);
    }
    for (int i = 2; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            fillDP(i, j);
        }
    }
    
    cout << DP[N][N].sum();
    
    return 0;
}
