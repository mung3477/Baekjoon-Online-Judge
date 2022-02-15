#include <iostream>
#define MOD 10007
using std::cin;
using std::cout;

int factorial[53]{1, 1, };
int NoSetsDP[53][53]{};

void prepareFactorial() {
    for (int i = 2; i <= 52; i++) factorial[i] = (long long)factorial[i - 1] * i % MOD;
}

int fastPower(int a, int p) {
    if (p == 1) return a;
    else if (p == 0) return 1;

    int half = fastPower(a, p / 2);
    int result = (long long)half * half % MOD;
    if (p % 2) result = (long long)result * a % MOD;

    return result;
}

int inverse(int a) {
    return fastPower(a, MOD - 2);
}

int combination(int n, int r) {
    return (long long)factorial[n] * inverse((long long)factorial[n - r] * factorial[r] % MOD) % MOD;
}

int noSets(int M, int N, int left) {
    if (NoSetsDP[M][N] != -1) return NoSetsDP[M][N];
    else {
        int memo;

        if (3 * left < N) memo = 0;
        else if (N < 4) memo = combination(M, N);
        else {
            int sum = 0;
            for (int i = 1; i <= N / 4; i++) {
                sum = (sum + (long long)combination(left, i) * noSets(M - 4 * i, N - 4 * i, left - i) % MOD) % MOD;
            }

            memo = (combination(M, N) - sum + MOD) % MOD;
        }

        return NoSetsDP[M][N] = memo;
    }
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    prepareFactorial();
    for (int i = 0; i <= 52; i++) {
        for (int j = 0; j <= 52; j++) {
            NoSetsDP[i][j] = -1;
        }
    }

    int N;
    cin >> N;

    cout << (combination(52, N) - noSets(52, N, 13) + MOD) % MOD;

    return 0;
}

