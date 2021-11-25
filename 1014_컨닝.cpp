#include <iostream>
#include <bitset>
#include <vector>
#include <utility>
#include <cmath>
using std::cin;
using std::cout;
using std::bitset;
using std::vector;
using std::pair;
using std::make_pair;

int max(int a, int b) {
    if (a < b) return b;
    else return a;
}
void fillCandidates(vector<pair<int, int>>& candidates, int numOfCases);
bool seatable(int arrangementA, int arrangementB);
bool seatCollide(int seat, int arrangement);

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int T;
    cin >> T;
    for (T; T > 0; T--) {
        int N, M;
        cin >> N >> M;
        
        int numOfCases = std::pow(2, M), ans = 0;
        int* seat = new int[N + 1]{};
        int** DP = new int*[N + 1];
        for (int i = 0; i <= N; i++) {
            DP[i] = new int[numOfCases]{0,};
        }
        
        vector<pair<int, int>> candidates;
        fillCandidates(candidates, numOfCases);
        
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < M; j++) {
                seat[i] = seat[i] << 1;
                
                char c;
                cin >> c;
                if (c == '.') {
                    seat[i] += 1;
                }
            }
        }
    
        
        for (int i = 1; i <= N; i++) {
            //cout << "i : " << i <<"\n";
            for (pair<int, int> candidateA : candidates) {
                //배치대로 앉을 수 있다면
                if (!seatCollide(seat[i], candidateA.first)) {
                    for (pair<int, int> candidateB : candidates) {
                        // 이전 좌석 배치와 상충되지 않는다면
                        if (seatable(candidateA.first, candidateB.first)) {
                            DP[i][candidateA.first] = max(DP[i][candidateA.first], DP[i - 1][candidateB.first] + candidateA.second);
                            
                            ans = max(ans, DP[i][candidateA.first]);
                        }
                    }
                }
            }
        }

        cout << ans << "\n";
        
        for (int i = 0; i <= N; i++) {
            delete[] DP[i];
        }
        delete DP, seat;
    }
    
    return 0;
}

void fillCandidates(vector<pair<int, int>>& candidates, int numOfCases) {
    bool flag;
    int ones = 0, prevEndedWithOne, curEndsWithOne;
    
    for (int i = 0; i < numOfCases; i++) {
        flag = true; 
        prevEndedWithOne = false;
        curEndsWithOne = false;
        ones = 0;
        int j = i;
        
        while (j != 0) {
            curEndsWithOne = j & 1;
            ones += curEndsWithOne;
            
            if (curEndsWithOne && prevEndedWithOne) {
                flag = false;
                break;
            }
            prevEndedWithOne = curEndsWithOne;
            j = j >> 1;
        }
        
        if (flag) {
            candidates.emplace_back(i, ones);
        }
    }
}
bool seatable(int arrangementA, int arrangementB) {
    int combined = (arrangementA | arrangementB), prevEndedWithOne = 0, curEndsWithOne;
    bool flag = true;
    
    //합쳤을 때 인접하게 사람이 앉으면 A와 B 배치는 불가능한 조합
    while (combined != 0) {
        curEndsWithOne = combined & 1;
        
        if (curEndsWithOne && prevEndedWithOne) {
            flag = false;
            break;
        }
        prevEndedWithOne = curEndsWithOne;
        combined = combined >> 1;
    }
        
    return flag;
}
bool seatCollide(int seat, int arrangement) {
    return arrangement != (seat & arrangement);
}
