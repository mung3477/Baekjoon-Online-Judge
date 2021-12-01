#include <iostream>
#define MOD 1000003
using std::cin;
using std::cout;

int** copy(int **matrix, const int& N);
int** multiply(int **A, int **B, const int& N);
int** power(int **adjMat, const long long& T, const int& N);

int main()
{
    int N, S, E;
    char c;
    long long T;
    int **adjMat;
    
    cin >> N >> S >> E >> T;
    adjMat = new int*[5 * N];
    for (int i = 0; i < 5 * N; i++) {
        adjMat[i] = new int[5 * N]{};
        
        //분할되어 생긴 정점인 경우, 모체와의 경로로 연결
        if (i % 5) {
            adjMat[i][i - 1] = 1;
        }
        //모체의 경우, 인접행렬에 따라 목적지+cost-1로 연결
        else {
            for (int j = 0; j < N; j++) {
                cin >> c;
                int cost = c - '0';
                
                if (cost >= 1) {
                    adjMat[i][5 * j + cost - 1] = 1;
                }
            }
        }
    }

    

    //T번 제곱
    int **powered = power(copy(adjMat, 5 * N), T, 5 * N);
    
    //답
    cout << powered[(S - 1) * 5][(E - 1) * 5];

    return 0;
}

int** copy(int **matrix, const int& N) {
    int **returnMat;
    returnMat = new int*[N];
    for (int i = 0; i < N; i++) {
        returnMat[i] = new int[N]{};
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            returnMat[i][j] = matrix[i][j];
        }
    }
    
    return returnMat;
}

//받은 행렬 무조건 release
int** multiply(int **A, int **B, const int& N) {
    int **returnMat;
    returnMat = new int*[N];
    for (int i = 0; i < N; i++) {
        returnMat[i] = new int[N]{};
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                returnMat[i][j] = (returnMat[i][j] + ((long long)A[i][k] * B[k][j]) % MOD) % MOD;
            }
        }
    }
    
    for (int i = 0; i < N; i++) delete[] A[i], B[i];
    delete[] A, B;
    return returnMat;
}

//받은 행렬 무조건 release
int** power(int **adjMat, const long long& T, const int& N) {
    int **returnMat;
    
    //terminate
    if (T == 1)  {
        returnMat = copy(adjMat, N);
    }
    
    else {
        //basic
        int **half = power(copy(adjMat, N), T / 2, N);
        
        int **doubleOfHalf = multiply(half, copy(half, N), N);
        
        if (T % 2) {
            returnMat = multiply(doubleOfHalf, copy(adjMat, N), N);
        }
        else returnMat = doubleOfHalf;
    }
    
    for (int i = 0; i < N; i++) delete[] adjMat[i];
    delete[] adjMat;
    
    return returnMat;
}
