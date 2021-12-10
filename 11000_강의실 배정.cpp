#include <cstdio>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;

//수업 시작 시각 오름차순 정렬. 같은 경우 일찍 끝나는 게 먼저.
bool comp(pair<int, int> a, pair<int, int> b){
    if(a.first == b.first){
        return a.second < b.second;
    }
    else return a.first < b.first;
}

int main(void)
{
    int N, t1, t2, used = 0, ans = 0, lastEnd = 0;
    vector<pair<int, int>> v;
    priority_queue<int, vector<int>, greater<int>> pq;

    scanf(" %d", &N);

    for(int i = 0; i < N; i++){
        scanf(" %d %d", &t1, &t2);
        v.push_back({t1, t2});
    }

    sort(v.begin(), v.end(), comp);

    for(int i = 0; i < N; i++){
        if(pq.empty()){
            pq.push(v[i].second);
        }
        else{
            //연강이 가능한 강의
            if(pq.top() <= v[i].first){
                pq.pop();
            }
            
            pq.push(v[i].second);
        }
    }

    printf("%d", pq.size());
    return 0;
}