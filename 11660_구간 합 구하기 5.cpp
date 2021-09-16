#include <iostream>
using std::cin;
using std::cout;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M, fromRow, fromCol, toRow, toCol, sum;
    int** DP;
    
    cin >> N >> M;
    
    DP = new int*[N + 1];
    for (int i = 1; i <= N; i++) {
        DP[i] = new int[N + 1]{};
        
        for (int j = 1; j <= N; j++) {
            cin >> DP[i][j];
            DP[i][j] += DP[i][j - 1];
        }
    }
    
    for (M; M > 0; M--) {
        sum = 0;
        cin >> fromRow >> fromCol >> toRow >> toCol;
        
        for (int i = fromRow; i <= toRow; i++) {
            sum += DP[i][toCol] - DP[i][fromCol - 1];
        }
        cout << sum << "\n";
    }
    
    return 0;
}
