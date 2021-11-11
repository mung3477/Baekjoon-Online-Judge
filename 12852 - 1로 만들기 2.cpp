#include <iostream>
#include <algorithm>
#include <stack>
#include <limits.h>
using std::cin;
using std::cout;
using std::fill;
using std::stack;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int* DP;
    int* backtrace;
    
    int N;
    cin >> N;
    
    DP = new int[N + 1];
    fill(DP, &DP[N + 1], INT_MAX);
    backtrace = new int[N + 1];
    fill(backtrace, &backtrace[N + 1], INT_MAX);
    
    DP[N] = 0;
    backtrace[N] = N;
    
    for (int i = N; 1 < i; i--) {
        //3으로 나누어 떨어질 경우
        if (i % 3 == 0) {
            if (DP[i / 3] > DP[i] + 1) {
                DP[i / 3] = DP[i] + 1;
                backtrace[i / 3] = i;
            }
        }
        //2로 나누어 떨어질 경우
        if (i % 2 == 0) {
            if (DP[i / 2] > DP[i] + 1) {
                DP[i / 2] = DP[i] + 1;
                backtrace[i / 2] = i;
            }
        }
        //공통
        if (DP[i - 1] > DP[i] + 1) {
            DP[i - 1] = DP[i] + 1;
            backtrace[i - 1] = i;
        }
    }
    
    cout << DP[1] << "\n";

    stack<int> backtracking;
    backtracking.push(1);
    for (int i = 1; i != N; i = backtrace[i]) {
        backtracking.push(backtrace[i]);
    }

    while (!backtracking.empty()) {
        cout << backtracking.top() << " ";
        backtracking.pop();
    }
    
    return 0;
}
