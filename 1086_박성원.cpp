#include <iostream>
#include <queue>
#include <utility>
#include <string>
using std::cin;
using std::cout;
using std::queue;
using std::pair;
using std::string;
using std::stoi;

int stringMod(const string& B, const int& K);
void fillTenPowMod(int *tenPowMod, const int& K);
void fillFactorial(long long *factorial, const int& N);
long long euclide(long long A, long long B);

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, K, done, tenPowMod[51]{}, *numbersMod;
    string *numbers;
    long long *factorial, **DP;
    bool **visited;
    queue<pair<int, int>> frontier;
    
    cin >> N;
    done = (1 << N) - 1;
    
    //numbers 구성
    numbers = new string[N];
    for (int i = 0; i < N; i++) {
        cin >> numbers[i];
    }
    
    cin >> K;
    
    // DP, visited 생성
    DP = new long long*[1 << N];
    visited = new bool*[1 << N];
    for (int i = 0; i < (1 << N); i++) {
        DP[i] = new long long[K]{};
        visited[i] = new bool[K]{};
    }
    
    //전 처리
    fillTenPowMod(tenPowMod, K);
    factorial = new long long[N + 1]{};
    fillFactorial(factorial, N);
    
    //numbers 각각의 K로 나눈 나머지 memoize
    numbersMod = new int[N]{};
    for (int i = 0; i < N; i++) {
        numbersMod[i] = stringMod(numbers[i], K);
    }
    
    // DP 첫 줄 채움
    for (int i = 0; i < N; i++) {
        int remain = numbersMod[i];
        DP[1 << i][remain] = 1;
        
        frontier.emplace(1 << i, remain);
        visited[1 << i][remain] = true;
    }
    
    while (!frontier.empty()) {
        pair<int, int> cur = frontier.front();
        frontier.pop();
        
        // 쓸 수 있는 거 하나 씩 씀
        for (int i = 0; i < N; i++) {
            //이미 썼으면 pass
            if ((cur.first & 1 << i) != 0) continue;
            
            //다음 DP 칸 값 계산
            int next = (cur.first | 1 << i);
            int remain = ((cur.second * (tenPowMod[numbers[i].length()])) % K + numbersMod[i]) % K;
            
            //DP 업데이트
            DP[next][remain] += DP[cur.first][cur.second];
            
            //frontier 업데이트
            if (!visited[next][remain]) {
                frontier.emplace(next, remain);
                visited[next][remain] = true;
            }
        }
    }
    
    long long gcd = euclide(DP[done][0], factorial[N]);
    
    cout << (DP[done][0] / gcd) << "/" << (factorial[N] / gcd);

    return 0;
}

int stringMod(const string& B, const int& K) {
    int modRes = 0;
    
    for (int i = 0; i < B.length(); i++) {
        modRes = (modRes * 10 + (int)B[i] - '0') % K;
    }
    return modRes;
}

void fillTenPowMod(int *tenPowMod, const int& K) {
    tenPowMod[0] = 1;
    for (int i = 1; i <= 50; i++) {
        tenPowMod[i] = (tenPowMod[i - 1] * 10) % K;
    }
}

void fillFactorial(long long *factorial, const int& N) {
    factorial[0] = 1;
    factorial[1] = 1;
    for (int i = 2; i <= N; i++) {
        factorial[i] = factorial[i - 1] * i;
    }
}

long long euclide(long long A, long long B) {
    long long r;
    while (B) {
        r = A % B;
        A = B;
        B = r;
    }
    
    return A;
}
