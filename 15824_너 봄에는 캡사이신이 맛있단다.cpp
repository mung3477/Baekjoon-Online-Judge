#include <iostream>
#include <vector>
#include <algorithm>
#define MOD 1000000007
using std::cin;
using std::cout;
using std::vector;
using std::sort;

long long pow(int a, int p) {
    if (p == 1) return a;
    else if (p == 0) return 1;

    long long half = pow(a, p / 2);
    long long returnValue = half * half % MOD;

    if (p % 2) returnValue = returnValue * a % MOD;

    return returnValue;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    long long t, answer = 0;
    vector<long long> scobilles;

    cin >> N;
    scobilles.push_back(-1);
    for (int i = 1; i <= N; i++) {
        cin >> t;
        scobilles.push_back(t);
    }

    sort(scobilles.begin(), scobilles.end());  

    for (int i = 1; i <= N; i++) {
        answer = (answer + (scobilles[i] * ((pow(2, i - 1) - pow(2, N - i) + MOD)) % MOD)) % MOD;
    }

    cout << answer;

    return 0;
}

