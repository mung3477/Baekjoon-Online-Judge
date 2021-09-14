#include <iostream>
using std::cin;
using std::cout;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, ans = 0;
    int* A;
    int** DP;
    
    cin >> N;
    A = new int[N + 1]{};
    DP = new int*[N + 1];
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        DP[i] = new int[2]{1, 1};
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j++) {
            if (A[i] < A[j] && DP[j][0] < DP[i][0] + 1) { DP[j][0] = DP[i][0] + 1; }
        }
    }
    
    for (int i = N; i >= 1; i--) {
        for (int j = i; j >= 1; j--) {
            if (A[i] < A[j] && DP[j][1] < DP[i][1] + 1) { DP[j][1] = DP[i][1] + 1; }
        }
    }
    
    for (int i = 1; i <= N; i++) {
        cout << DP[i][0] << "\t" << DP[i][1] << "\n";
        ans = (ans < DP[i][0] + DP[i][1] ? DP[i][0] + DP[i][1] : ans);
    }
    
    cout << ans - 1;
    
    return 0;
}
