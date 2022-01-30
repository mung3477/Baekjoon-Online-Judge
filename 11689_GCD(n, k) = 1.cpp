#include <iostream>
#include <vector>
#include <math.h>
using std::cin;
using std::cout;
using std::vector;
using std::sqrt;
vector<long long> primeFactors;


int main(void) {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    long long N, ans;
    int range;
    cin >> N;

    ans = N;
    range = (int)(sqrt(N) + 1);

    for (int i = 2; i < range; i++) {
        if (N % i == 0) {
            primeFactors.push_back(i);
            while (N % i == 0) N /= i;
        }
    }
    if (N != 1) primeFactors.push_back(N);
    

    for (long long factor : primeFactors) {
        ans = ans - ans / factor;
    }

    cout << ans;
    return 0;
}
