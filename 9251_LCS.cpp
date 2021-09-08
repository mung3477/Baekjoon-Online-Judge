#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

int bigger(int a, int b) {
    if (a > b) return a;
    else return b;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int longest = 0;
    int** LCS;
    string a, b;
    cin >> a >> b;
    
    //LCS[a][b]
    LCS = new int*[a.length() + 1];
    for (int i = 0; i <= a.length(); i++) {
        LCS[i] = new int[b.length() + 1]{};
    }
    
    //initialize
    for (int i = 0; i <= a.length(); i++) {
        LCS[i][0] = 0;
    }
    for (int j = 0; j <= b.length(); j++) {
        LCS[0][j] = 0;
    }
    
    for (int i = 1; i <= a.length(); i++) {
        for (int j = 1; j <= b.length(); j++) {
            if (a.at(i - 1) == b.at(j - 1)) {
                LCS[i][j] = LCS[i - 1][j - 1] + 1;    
            }
            else {
                LCS[i][j] = bigger(LCS[i - 1][j], LCS[i][j - 1]);
            }
        }
    }
    
    cout << LCS[a.length()][b.length()];
    
    return 0;
}
