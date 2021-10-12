#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::vector;  //starts with index 0

vector<long long> DP;

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

//DP[index] 값이 target 이하인 index 중 가장 큰 index 찾기
int find(int left, int right, long long target) {
    if (left == right) {
        if (DP[left] > target) return -1;
        else return left;
    }
    
    int mid = (left + right) / 2 + 1;
    if (DP[mid] <= target) return find(mid, right, target);
    else return find(left, mid - 1, target);
}

int main()
{
    int N, S, minDist;
    vector<int> sequence;
    
    cin >> N >> S;
    minDist = N + 1;
    for (int i = 0; i < N; i++) {
       int input;
       cin >> input;
       sequence.push_back(input);
       if (i) DP.push_back(DP[i - 1] + input);
       else DP.push_back(input);
    }
    
    for (int i = 0; i < N; i++) {
        if (DP[i] == S) { 
            minDist = min(minDist, i + 1);
        }
        else if (DP[i] > S) {
            int found = find(0, i, DP[i] - S);
            if (found != -1) minDist = min(minDist, i - found);
        }
    }

    cout << (minDist == N + 1 ? 0 : minDist);
    
    return 0;
}
