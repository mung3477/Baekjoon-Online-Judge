#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
using std::fill;

int* given;             //1 ~ N
short** isPalindrome;    //1 ~ N, 1 ~ N. -1: not assessed yet, 0: false, 1: true

short assess(int S, int E) {
    //only works for non-assessed element
    if (isPalindrome[S][E] == -1) {
        //구간 길이 2
        if (S + 1 == E) 
            isPalindrome[S][E] = (given[S] == given[E]);
        //구간 길이 3 이상
        else {
            isPalindrome[S][E] = (assess(S + 1, E - 1) && (given[S] == given[E]));
        }
    }
    return isPalindrome[S][E];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M;
    cin >> N;
    
    //dynamically allocate arrays
    given = new int[N + 1]{};
    isPalindrome = new short*[N + 1]{};
    for (int i = 1; i <= N; i++) {
        isPalindrome[i] = new short[N + 1]{};
        fill(isPalindrome[i], &isPalindrome[i][N + 1], -1);
    }
        
    
    for (int i = 1; i <= N; i++) {
        cin >> given[i];
        isPalindrome[i][i] = 1;
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            assess(i, j);
        }
    }
    
    cin >> M;
    for (M; M > 0; M--) {
        int S, E;
        cin >> S >> E;
        
        cout << isPalindrome[S][E] << "\n";
    }
    
    for (int i = 1; i <= N; i++)
        delete[] isPalindrome[i];
    delete[] given, isPalindrome;
    
    return 0;
}
