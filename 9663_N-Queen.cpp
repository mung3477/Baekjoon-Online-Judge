#include <iostream>
using std::cin;
using std::cout;


void use(int row, int col, bool* rowUsed, bool* colUsed, bool* RUDiagUsed, bool* RDDiagUsed, int N) {
    rowUsed[row] = !rowUsed[row];
    colUsed[col] = !colUsed[col];
    RUDiagUsed[row + col - 1] = !RUDiagUsed[row + col - 1];
    RDDiagUsed[N - row + col] = !RDDiagUsed[N - row + col];
}

void NQueen(int row, bool* rowUsed, bool* colUsed, bool* RUDiagUsed, bool* RDDiagUsed, int& ans, int N) {
    if (row == N + 1) {
        ans++;
        return;
    }
    
    for (int col = 1; col <= N; col++) {
        //if that square is usable
        if (!colUsed[col] && !RUDiagUsed[row + col - 1] && !RDDiagUsed[N - row + col]) {
            use(row, col, rowUsed, colUsed, RUDiagUsed, RDDiagUsed, N);
            NQueen(row + 1, rowUsed, colUsed, RUDiagUsed, RDDiagUsed, ans, N);
            use(row, col, rowUsed, colUsed, RUDiagUsed, RDDiagUsed, N);
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, ans = 0;
    bool* rowUsed;
    bool* colUsed;
    bool* RUDiagUsed;
    bool* RDDiagUsed;
    
    cin >> N;
    
    //1 ~ N
    rowUsed = new bool[N + 1]{};
    colUsed = new bool[N + 1]{};
    
    //1 ~ 2N - 1
    RUDiagUsed = new bool[2 * N]{};
    RDDiagUsed = new bool[2 * N]{};
    
    for (int col = 1; col <= N; col++) {
        
        use(1, col, rowUsed, colUsed, RUDiagUsed, RDDiagUsed, N);
        
        NQueen(2, rowUsed, colUsed, RUDiagUsed, RDDiagUsed, ans, N);
        
        use(1, col, rowUsed, colUsed, RUDiagUsed, RDDiagUsed, N);
    }

    cout << ans;
    
    return 0;
}
