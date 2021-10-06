#include <iostream>
#include <vector>
#include <utility>
using std::cin;
using std::cout;
using std::vector;
using std::fill;

vector<int> primes;
vector<long long> DP;

void seiveOfErathosthenes() {
    bool isPrime[4000001]{};
    fill(&isPrime[2], &isPrime[4000001], true);
    
    for (int i = 2; i * i <= 4000000; i++) {
        if (!isPrime[i]) continue;
        
        for (int j = i; i * j <= 4000000; j++) 
            isPrime[i * j] = false;
        
    }
    
    for (int i = 2; i <= 4000000; i++) 
        if (isPrime[i]) primes.push_back(i);
}

bool find(int left, int right, long long target) {
    if (left == right)
        return (DP.at(left) == target);
    
    int mid = (left + right) / 2;
    if (DP.at(mid) == target) return true;
    else if (DP.at(mid) < target) return find(mid + 1, right, target);
    else return find(left, mid, target);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int cases = 0, N;
    cin >> N;
    
    seiveOfErathosthenes();
    DP.push_back(0);    //1 ~ K 그 자체가 입력값과 같은 경우
    for (auto it = primes.begin(); it != primes.end(); it++) {
        DP.push_back(*it + DP.back());
    }
    
    for (int K = 0; K < DP.size(); K++) {
        if (N <= DP.at(K))
            if (find(0, DP.size() - 1, DP.at(K) - N)) 
                cases++;
    }
    
    cout << cases;
    
    return 0;
}
