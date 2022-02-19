#include <iostream>
#define MOD 1000000007
using std::cin;
using std::cout;

int ***map, ***DP, N;

int** matrixMultiplication(int** A, int** B);
int** fastPower(int** A, int p);

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T, D;
    cin >> T >> N >> D;

    map = new int**[T + 1]{};
    DP = new int**[T + 1]{};
    for (int t = 0; t <= T; t++) {
        map[t] = new int*[N + 1]{};
        DP[t] = new int*[N + 1]{};
        for (int i = 0; i <= N; i++) {
            map[t][i] = new int[N + 1]{};
            DP[t][i] = new int[N + 1]{};
        }
    }

    for (int i = 1; i <= N; i++) {
        DP[0][i][i] = 1;
    }

    for (int i = 1; i <= T; i++) {
        int M;
        cin >> M;
        for (int j = 1; j <= M; j++) {
            int a, b, c;
            cin >> a >> b >> c;

            map[i][a][b] = c;
            if (i == 1) DP[i][a][b] = c;
        }
    }

    for (int t = 2; t <= T; t++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                for (int k = 1; k <= N; k++) {
                    DP[t][i][j] = (DP[t][i][j] + (long long)DP[t - 1][i][k] * map[t][k][j] % MOD) % MOD;
                }
            }
        }
    }

    int** ans;
    if (D <= T) ans = DP[D];
    else ans = matrixMultiplication(fastPower(DP[T], D / T), DP[D % T]);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }

    for (int t = 0; t <= T; t++) {
        for (int i = 0; i <= N; i++) {
            delete[] DP[t][i], map[t][i];
        }
        delete[] DP[t], map[t];
    }

    delete[] DP, map;

    if (D > T) {
        for (int i = 0; i <= N; i++) delete[] ans[i];
        delete[] ans;
    }
    return 0;
}

int** matrixMultiplication(int** A, int** B) {
    int** result = new int*[N + 1]{};
    for (int i = 0; i <= N; i++) result[i] = new int[N + 1]{};

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                result[i][j] = (result[i][j] + (long long)A[i][k] * B[k][j] % MOD) % MOD;
            }
        }
    }

    return result;
}

int** fastPower(int** A, int p) {
    if (p == 1) {
        int** result = new int*[N + 1]{};
        for (int i = 0; i <= N; i++) {
            result[i] = new int[N + 1]{};
            for (int j = 0; j <= N; j++) {
                result[i][j] = A[i][j];
            }
        }

        return result;
    }
    
    int** half = fastPower(A, p / 2);
    int** result = matrixMultiplication(half, half);

    for (int i = 0; i <= N; i++) delete[] half[i];
    delete[] half;

    if (p % 2 == 0) return result;
    else {
        int** realResult = matrixMultiplication(result, A);
        for (int i = 0; i <= N; i++) delete[] result[i];
        delete[] result;

        return realResult;
    }

}
