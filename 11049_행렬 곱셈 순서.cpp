#include <iostream>
#include <utility>
#include <algorithm>
#include <limits.h>
#define INIT -1
using std::cin;
using std::cout;
using std::pair;
using std::make_pair;
using std::fill;

long long** minCalc;             //from to, min 연산 횟수 저장
pair<int, int>** minCalcResult; //min 횟수 연산의 결과 저장
pair<int, int>* matrices;

long long findMin(int from, int to) {
    if (minCalc[from][to] == INIT) {
        //행렬 1개
        if (from == to) {
            minCalc[from][to] = 0;
            minCalcResult[from][to] = matrices[from];
        }
        //행렬 2개
        else if (from + 1 == to) {
            minCalc[from][to] = matrices[from].first * matrices[from].second * matrices[to].second;
            minCalcResult[from][to] = make_pair(matrices[from].first, matrices[to].second);
        }
        //행렬 3개 이상
        else {
            minCalc[from][to] = LLONG_MAX;  //min 비교가 제대로 될 수 있도록
        
            for (int mid = from; mid < to; mid++) {
                long long newCalc = findMin(from, mid) + findMin(mid + 1, to) + minCalcResult[from][mid].first * minCalcResult[from][mid].second * minCalcResult[mid + 1][to].second;
                if (newCalc <= minCalc[from][to]) {
                    minCalc[from][to] = newCalc;
                    minCalcResult[from][to] = make_pair(minCalcResult[from][mid].first, minCalcResult[mid + 1][to].second);
                }
            }
        }
    }
    
    return minCalc[from][to];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N;
    cin >> N;
    
    matrices = new pair<int, int>[N + 1]{};
    minCalc = new long long*[N + 1]{};
    minCalcResult = new pair<int, int>*[N + 1]{};
    for (int i = 1; i <= N; i++) {
        minCalc[i] = new long long[N + 1];
        fill(minCalc[i], &minCalc[i][N + 1], INIT);

        minCalcResult[i] = new pair<int, int>[N + 1]{};
    }
    
    for (int i = 1; i <= N; i++) {
        int row, col;
        cin >> row >> col;
        
        matrices[i].first = row;
        matrices[i].second = col;
    }
    
    for (int from = 1; from <= N; from++) {
        for (int to = from; to <= N; to++) {
            findMin(from, to);
        }
    }
    
    cout << minCalc[1][N];
    
    for (int i = 1; i <= N; i++) {
        delete[] minCalc[i], minCalcResult[i];
    }
    delete[] minCalc, minCalcResult, matrices;
    
    return 0;
}
