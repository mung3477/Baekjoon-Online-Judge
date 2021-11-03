#include <iostream>
#define MOD 1000000007
using std::cin;
using std::cout;

int** adjMat;

int** copyAdjMat() {
    int** copiedMatrix = new int*[8];
        for (int i = 0; i <= 7; i++) {
            copiedMatrix[i] = new int[8]{};
            for (int j = 0; j <= 7; j++) copiedMatrix[i][j] = adjMat[i][j];
        }
    return copiedMatrix;
}

//frees both matrices
int** matMul(int** A, int** B, bool square) {
    int** result = new int*[8];
    for (int i = 0; i <= 7; i++) result[i] = new int[8]{};
    
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            for (int k = 0; k <= 7; k++) 
                result[i][j] = (result[i][j] + (long long)A[i][k] * B[k][j]) % MOD;
        }
    }
    
    for (int i = 0; i <= 7; i++) {
        if (!square) delete[] A[i], B[i];
        else delete[] A[i];
    }
    if (!square) delete[] A, B;
    else delete[] A;
    
    return result;
}

int** matPow(int** matrix, int D) {
    //function works with D bigger than 1
    if (D == 1) {
        return copyAdjMat();
    }
    
    int** half = matPow(matrix, D / 2);
    
    int** result = matMul(half, half, true);
    
    if (D % 2) {
        int** copiedMatrix = copyAdjMat();
        
        result = matMul(result, copiedMatrix, false);
    }
    
    return result;
}

int main()
{
    adjMat = new int*[8];
    
    adjMat[0] = new int[8]{0, 1, 0, 0, 0, 0, 0, 1};
    adjMat[1] = new int[8]{1, 0, 1, 0, 0, 0, 0, 1};
    adjMat[2] = new int[8]{0, 1, 0, 1, 0, 0, 1, 1};
    adjMat[3] = new int[8]{0, 0, 1, 0, 1, 0, 1, 0};
    adjMat[4] = new int[8]{0, 0, 0, 1, 0, 1, 0, 0};
    adjMat[5] = new int[8]{0, 0, 0, 0, 1, 0, 1, 0};
    adjMat[6] = new int[8]{0, 0, 1, 1, 0, 1, 0, 1};
    adjMat[7] = new int[8]{1, 1, 1, 0, 0, 0, 1, 0};
    
    int D;
    cin >> D;
    
    int** result = matPow(adjMat, D);
    
    cout << result[0][0];
    
    return 0;
}
