#include <iostream>
using std::cin;
using std::cout;

int** matrixMultiplication(int** P, int** Q, int N) {
    int** result = new int*[N + 1];
    for (int i = 1; i <= N; i++) {
        result[i] = new int[N + 1]{};
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                result[i][j] += (P[i][k] * Q[k][j]) % 1000;
                result[i][j] = (result[i][j] % 1000);
            }
        }
    }
    
    return result;
}

int** power(int** A, long long B, int N) {
    int** result;
    int** temp;
    
    if (B == 1) {
        result = new int*[N + 1];
        
        for (int i = 1; i <= N; i++) {
            result[i] = new int[N + 1];
            for (int j = 1; j <= N; j++) {
                result[i][j] = A[i][j];
            }
        }
        
        return result;
    }
    
    int** half = new int*[N + 1];
    for (int i = 1; i <= N; i++) {
        half[i] = new int[N + 1]{};
    }
    
    half = power(A, B / 2, N);
    
    result = matrixMultiplication(half, half, N);
    
    for (int i = 1; i <= N; i++) {
        delete[] half[i];
    }
    delete[] half;
    
    if (B % 2) {
        temp = result;
        result = nullptr;
        result = matrixMultiplication(temp, A, N);
        
        for (int i = 1; i <= N; i++) {
            delete[] temp[i];
        }
        delete[] temp;
    }
    
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int** result;
    int** A;
    int N;
    long long B;
    cin >> N >> B;
    
    A = new int*[N + 1];
    result = new int*[N + 1];
    for (int i = 1; i <= N; i++) {
        A[i] = new int[N + 1];
        result[i] = new int[N + 1]{};
        for (int j = 1; j <= N; j++) {
            cin >> A[i][j];
            A[i][j] = A[i][j] % 1000;
        }
    }
    
    result = power(A, B, N);
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << result[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
