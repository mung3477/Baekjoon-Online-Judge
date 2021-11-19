#include <iostream>
#include <utility>
using std::cin;
using std::cout;
using std::pair;

int ccw(const pair<int, int>& A, const pair<int, int>& B, const pair<int, int>& C) {
    long long S = (long long)(B.first - A.first) * (C.second - A.second) - (long long)(B.second - A.second) * (C.first - A.first);
    
    if (S > 0) return 1;
    else if (S < 0) return -1;
    else return 0;
}

int main()
{
    pair<int, int> A, B, C, D;
    
    cin >> A.first >> A.second >> B.first >> B.second >> C.first >> C.second >> D.first >> D.second;
    
    int L1 = ccw(A, B, C) * ccw(A, B, D);
    int L2 = ccw(C, D, A) * ccw(C, D, B);
    
    if (L1 == 0 && L2 == 0) {
        //좌->우가 A->B, C->D 가 되게끔 정렬
        if (A > B) swap(A, B);
        if (C > D) swap(C, D);
        
        cout << (A <= D && C <= B);
    }
    else cout << (L1 <= 0 && L2 <= 0);

    return 0;
}
