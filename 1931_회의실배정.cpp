#include <cstdio>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

//second 오름 차순, 동률 시 회의 길이 오름차순
bool comp(pair<int, int> a, pair<int, int> b){
    if(a.second > b.second) return false;
    else if (a.second == b.second){
        if(a.first > b.first) return false;
        else return true;
    }
    else return true;
}

int main(void)
{
    int N, t1, t2, cur, ans = 0;
    vector<pair<int, int>> v;
    
    scanf(" %d", &N);
    for(int i = 0; i < N; i++){
        scanf(" %d %d", &t1, &t2);
        v.push_back({t1, t2});
    }

    sort(v.begin(), v.end(), comp);

    int i = 0;
    cur = v[i].second;
    ans++;
    for(i = 1; i < N; i++){
        if((v[i]).first < cur);
        else{
            cur = (v[i]).second;
            ans++;
        }
    } 

    printf("%d", ans);
    return 0;
}

