#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
using std::cin;
using std::cout;
using std::sort;
using std::vector;
using std::pair;        //weight, value
using std::priority_queue;

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, K;
    long long valueSum = 0;
    vector<pair<int, int>> jewels;
    jewels.emplace_back(-1, -1);
    vector<int> bags;
    bags.push_back(-1);
    priority_queue<int> available;
    
    cin >> N >> K;
    
    for (int i = 1; i <= N; i++) {
        pair<int, int> temp;
        cin >> temp.first >> temp.second;
        
        jewels.push_back(temp);
    }

    
    for (int i = 1; i <= K; i++) {
        int capacity;
        cin >> capacity;
        bags.push_back(capacity);
    }
    
    sort(jewels.begin(), jewels.end());
    sort(bags.begin(), bags.end());
    
    //i for bags, j for jewels
    for (int i = 1, j = 1; i <= K; i++) {
        while (j <= N && jewels.at(j).first <= bags.at(i)) 
            available.push(jewels.at(j++).second);
        
        if (!available.empty()) {
            valueSum += available.top();
            available.pop();
        }
    }
    
    cout << valueSum;
    
    return 0;
}
