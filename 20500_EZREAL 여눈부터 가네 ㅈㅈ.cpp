#include <iostream>
#define MOD 1000000007
using std::cin;
using std::cout;

long long power(int B, int p) {
    if (p == 1) return B;

    long long halfPowered = power(B, p / 2);
    long long retVal = (halfPowered * halfPowered) % MOD;
    if (p % 2) retVal = retVal * B % MOD;

    return retVal;
}

long long divideAndMod (int A, int B) {
    return (A * power(B, MOD - 2)) % MOD;
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N;
    cin >> N;

    long long ans = 0, comb = 1, cur;
    long long combination[1515]{1, };

    // 1이 0개 -> N - 1개 (맨 마지막 자리만 5)
    for (int i = 0; i < N; i++) {
        cur = 5 * (N - i) + i;
        // combination 계산
        if (i) 
            comb = (combination[N - 1 - i] ? combination[N - 1 - i] : combination[i] = divideAndMod((combination[i - 1] * (N - i) % MOD), i));
        
        // 15의 배수를 만들 수 있는 조합이라면
        if (cur % 3 == 0) {
            ans = (ans + comb) % MOD;
        }
    }

    cout << ans;
    
    return 0;
}

