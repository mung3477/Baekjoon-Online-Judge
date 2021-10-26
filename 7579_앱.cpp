#include <iostream>
#include <vector>
#define maxCost 10000
using std::cin;
using std::cout;
using std::vector;

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int main()
{
    int N, M;
    vector<int> Memories;
    vector<int> Costs;
    long long** DP;   //[item index][cost] : 확보한 메모리 양
        
    cin >> N >> M;
    
    for (int i = 0; i < N; i++) {
        int memory;
        cin >> memory;
        Memories.push_back(memory);
    }
    for (int i = 0; i < N; i++) {
        int cost;
        cin >> cost;
        Costs.push_back(cost);
    }
    
    DP = new long long*[N];
    for (int i = 0; i < N; i++) 
        DP[i] = new long long[maxCost + 1]{};   
    
    DP[0][Costs.at(0)] = Memories.at(0);
    
    
    for (int i = 1; i < N; i++) {
        for (int j = 0; j <= maxCost; j++) {
            //max(쓰기, 안쓰기)
            DP[i][j] = max((j >= Costs.at(i) ? DP[i - 1][j - Costs.at(i)] + Memories.at(i) : 0), DP[i - 1][j]);
        }
    }
    
    for (int j = 0; j <= maxCost; j++) {
        if (DP[N - 1][j] >= M) {
            cout << j;
            break;
        }
    }
    
    return 0;
}
