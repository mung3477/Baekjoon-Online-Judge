#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

bool comp(int a, int b){
    if(a > b) return true;
    else return false;
}

int main(void)
{
    int N, L;
    queue<int> q;
    vector<int> v;

    scanf(" %d %d", &N, &L);
    for(int i = 0; i < N; i++){
        int t;
        scanf(" %d", &t);
        v.push_back(t);
    }
    
    //vector를 내림차순 정렬하고 마지막부터 queue에 넣어 queue 안에서 오름차순 정렬
    sort(v.begin(), v.end(), comp);
    while(!v.empty()){
        int t = v.back();
        v.pop_back();
        q.push(t);
    }

    int count = 0;
    double start = 0;

    while(!q.empty()){
        //테이프 처음 뗌
        if(start == 0){
            start = q.front() - 0.5;
            q.pop();
            count++;
        }
        //테이프 쓰는 중
        else{
            //그 테이프 계속 쓸 수 있음
            if(q.front() + 0.5 <= start + L){
                q.pop();
            }
            //테이프 새로 뜯어야함
            else{
                start = 0;
            }
        }
    }
    printf("%d", count);
    return 0;
}