#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::sort;
using std::fill;

vector<pair<int, int>> cables;
pair<int, int>* LIS;
vector<int> trace;  //cables[i]를 LIS의 trace[i] 자리에 넣었음.
vector<int> answer;

struct Comp {
    bool operator()(pair<int, int>& A, pair<int, int>& B) {
        return A.first < B.first;
    }
} comp;

//처음으로 target.second보다 LIS[position]의 값이 커지는 position을 찾음.
int fitsAt(int left, int right, pair<int, int>& target) {
    if (left == right) return left;
    
    int mid = (left + right) / 2;
    
    //같은 값을 찾을 수는 없음
    if (LIS[mid].second < target.second) return fitsAt(mid + 1, right, target);
    else return fitsAt(left, mid, target);
}

int main()
{
    int N;
    cin >> N;
    LIS = new pair<int, int>[N + 1]{};
    
    pair<int, int> init = std::make_pair(1000000, 1000000);
    fill(LIS, &LIS[N + 1], init);
    
    for (int i = 0; i < N; i++) {
        int from, to;
        cin >> from >> to;
        cables.emplace_back(from ,to);
    }
    
    sort(cables.begin(), cables.end(), comp);
    
    int length = 1;
    LIS[0] = cables.at(0);
    trace.push_back(0);
    
    for (int i = 1; i < cables.size(); i++) {
        /*
            i번째 cable을 쓸 수 있는 자리를 찾음.   
            LIS[position - 1]은 cables[i]보다 작고, LIS[position]은 cables(i)보다 크다.
        */
        int position = fitsAt(0, length, cables.at(i));
        LIS[position] = cables.at(i);
        trace.push_back(position);
        
        if (position == length) length++;
    }
    
    cout << N - length << "\n";
    
    //최장길이 position에 접근했던 기록이 보일 때를 제외하고 나머지 cable을 전부 저장
    int target = length - 1;
    for (int i = trace.size() - 1; i >= 0; i--) {
        if (trace.at(i) == target) 
            target--;
        else {
            answer.push_back(cables.at(i).first);
        }
    }
    
    sort(answer.begin(), answer.end());
    for (int elem : answer)
        cout << elem << "\n";
    
    return 0;
}
