#include <iostream>
#define MOD 1000000007
using std::cin;
using std::cout;

int factorial[4000001]{1, 1,};

void combination(int N, int K);
int fastPower(int A, int p);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int i = 2; i <= 4000000; i++) {
        factorial[i] = (long long)factorial[i - 1] * i % MOD;
    }

    int M, N, K;
    cin >> M;
    for (int i = 1; i <= M ; i++) {
        cin >> N >> K;
        combination(N, K);
    }

    return 0;
}

void combination(int N, int K) {
    cout << (long long)factorial[N] * fastPower((long long)factorial[K] * factorial[N - K] % MOD, MOD - 2) % MOD << "\n";
}

int fastPower(int A, int p) {
    if (p < 2) return p == 1 ? A : 1;
    
    int half = fastPower(A, p / 2);
    int result = (long long)half * half % MOD;
    if (p % 2) result = (long long)result * A % MOD;

    return result;
}
