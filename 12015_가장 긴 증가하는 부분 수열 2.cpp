#include <iostream>
using std::cin;
using std::cout;

/*
    길이 i짜리 가장 긴 증가하는 부분 수열을 만드는 숫자를 increasingSq[i]에 저장 
    index 1부터 사용
*/
int* increasingSq;
int* given;

//target 미만의 가장 큰 element가 있는 increasingSq의 index를 반환
int upperBound(int left, int right, int target) {
    if (left == right) return left;
    
    int mid = (left + right) / 2 + 1;
    if (increasingSq[mid] < target) return upperBound(mid, right, target);
    else return upperBound(left, mid - 1, target);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, LISLength = 0;
    cin >> N;
    
    increasingSq = new int[N + 1]{};
    given =  new int[N + 1]{};
    
    for (int i = 1; i <= N; i++) {
        cin >> given[i];
    }
    
    
    increasingSq[1] = given[1];
    LISLength++;
    for (int i = 2; i <= N; i++) {
        int appropriatePos = upperBound(0, LISLength, given[i]) + 1;
        increasingSq[appropriatePos] = given[i];
        
        if (LISLength + 1 == appropriatePos) {
            LISLength = appropriatePos;
        }
    }
    
    cout << LISLength;
    
    return 0;
}
