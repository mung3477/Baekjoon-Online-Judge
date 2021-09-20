#define mod 1000000007
#include <iostream>
using std::cin;
using std::cout;

int euclide(int N, int S) {
    int a, b, r;
    //a가 더 크게 조정
    if (N > S) {
        a = N;
        b = S;
    } 
    else {
        a = S;
        b = N;
    }
    
    while (b) {
        r = a % b;
        a = b;
        b = r;
    }
    
    return a;
}

long long power(int S, int p) {
    if (S == 1) return 1;
    if (p == 1) return S;
    
    long long half = power(S, p / 2);
    long long result = half * half % mod;
    if (p % 2) result = result * S % mod;
    
    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int M, N, S, gcd;
    long long result = 0, nInverse = 0;
    
    cin >> M;
    
    for (M; M > 0; M--) {
        cin >> N >> S;
        
        //기약분수
        gcd = euclide(N, S);
        N /= gcd;
        S /= gcd;
        
        //분모 1,000,000,007 - 2 제곱
        nInverse = power(N, mod - 2);
        
        //결과
        result = (result + ((S * nInverse) % mod)) % mod;
    }
    cout << result;
    
    return 0;
}
