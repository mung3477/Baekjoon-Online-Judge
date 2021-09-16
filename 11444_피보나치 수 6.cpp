#include <iostream>
using std::cin;
using std::cout;

const long long mod = 1000000007;

long long** matrixMultiple(long long** A, long long** B) {
    long long** C = new long long*[2];
    C[0] = new long long[2]{};
    C[1] = new long long[2]{};
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                C[i][j] = (C[i][j] + ((A[i][k] * B[k][j]) % mod)) % mod;
            
            }
        }
    }
    
    return C;
}

long long** power(long long** A, long long N) {
    if (N == 1) {
        long long** F = new long long*[2];
        F[0] = new long long[2]{1, 1};
        F[1] = new long long[2]{1, 0};
        
        return F;
    } 
    else {
        long long** result;
        long long** temp;
        
        temp = power(A, N / 2);
        result = matrixMultiple(temp, temp);
        
        //free power's result memory
        delete[] temp[0], temp[1], temp;
        
        if (N % 2) {
            temp = result;
            result = nullptr;
            
            result = matrixMultiple(temp, A);
            //free matrixMultiple's result memory
            delete[] temp[0], temp[1], temp;
        }
        
        return result;
    }
}

long long fibo(long long N) {
    if (N <= 2) return 1;

    long long** F = new long long*[2];
    F[0] = new long long[2]{1, 1};
    F[1] = new long long[2]{1, 0};
    
    long long** powered = power(F, N);
    
    return powered[1][0];
}

int main()
{
   std::ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   cout.tie(NULL);
   
   long long N;
   cin >> N;
   
   cout << fibo(N);
   
   return 0;
}
