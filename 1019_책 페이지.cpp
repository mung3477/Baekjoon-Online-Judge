#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
using std::pow;


int ans[10];

int length(int A) {
    int length = (A == 0 ? 1 : 0);
    while (A) {
        length++;
        A /= 10;
    }
    return length;
}

void howManyNumbers(int A, bool first) {
    if (A < 10) {
        for (A; A >= 0; A--) ans[A]++;
    }
    else {
        /*
            K = A.length() - 1 (A 자리수 - 1, 한 자리수 작은 9로 꽉찬 수의 9의 개수) 
            자리 수가 하나 작은 "0" ~ 999...99까지 0 ~ 9 개수 업데이트
            답은 1부터.
        */
        int k = length(A) - 1;
        int zeroToNines[10]{};
        
        for (int i = 0; i <= 9; i++) {
            zeroToNines[i] = pow(10, k - 1) * k;
            
            if (first) {
                ans[i] += zeroToNines[i];
                
                if (i == 0) {
                    ans[0] -= (pow(10, k) - 1) / 9;
                }
            }
        }
        
        /* 
            10...00 ~ (A 첫번째 수 - 1)999...9 까지 숫자 개수 세기
        */
        int AFirst = A / pow(10, length(A) - 1), ARest = A % (int)pow(10, length(A) - 1);
        
        for (int i = (first ? 1 : 0); i < AFirst; i++) {
            for (int j = 0; j <= 9; j++) 
                ans[j] += zeroToNines[j];
            ans[i] += pow(10, k);
        }

        /* 
            (A 첫번재 수)00...00 ~ N까지 숫자 개수 세기
        */
        ans[AFirst] += ARest + 1;
        if (length(ARest) + 1 !=  length(A)) {
            ans[0] += (length(A) - length(ARest) - 1) * (ARest ? ARest + 1 : 1);
        }
            
        howManyNumbers(ARest, false);
        
    }
}

int main()
{
    int N;
    cin >> N;
    
    for (int i = 0; i <= 9; i++) ans[i] = 0;
    
    if (N < 10) 
        for (int i = 1; i <= N; i++) 
            ans[i] = 1;
    else {
        howManyNumbers(N, true);
    }
    
    for (int i = 0; i <= 9; i++) {
        cout << ans[i] << " ";
    }
    
    return 0;
}
