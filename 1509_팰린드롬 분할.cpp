#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

bool** isPal;
bool** visited;
int* maxPalLength;       //s[i]로 끝나는 palindrome 중 제일 긴 것의 길이
int* minPalDiv;
string s;

bool CheckIsPal(int i, int j) {
    if (!visited[i][j]) {
        if (i > j) isPal[i][j] = false;
        else if (i == j) isPal[i][j] = true;
        else isPal[i][j] = (s.at(i - 1) == s.at(j - 1)) && (i + 1 > j - 1 || CheckIsPal(i + 1, j - 1));
        visited[i][j] = true;
    }
    return isPal[i][j];
}

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N;
    
    
    cin >> s;
    
    N = s.length();
    maxPalLength = new int[N + 1]{};
    minPalDiv = new int[N + 1]{};
    isPal = new bool*[N + 1];
    visited = new bool*[N + 1];
    for (int i = 0; i <= N; i++) {
        isPal[i] = new bool[N + 1]{};
        visited[i] = new bool[N + 1]{};
    }
    
    /** Check palindrome for all substrings */
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            CheckIsPal(i, j);
        }
    }
    
    minPalDiv[0] = 0;
    for (int j = 1; j <= N; j++) {
        //initial value: s[j] doesn't make a new palindrome
        minPalDiv[j] = minPalDiv[j - 1] + 1; 
        
        //check for all possibilities of new palindrome using s[j], and find the best one
        for (int i = 1; i <= j; i++) 
            if (isPal[i][j]) minPalDiv[j] = min(minPalDiv[j], minPalDiv[j - (j - i + 1)] + 1);
    }
    
    cout << minPalDiv[N];
    
    return 0;
}
