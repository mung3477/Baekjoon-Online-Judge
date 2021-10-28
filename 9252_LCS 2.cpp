#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;

struct trace {
    int prevS1;
    int prevS2;
    bool used;   
    
    trace(): prevS1(-1), prevS2(-1), used(false) {};
    trace(int prevS1, int prevS2, bool used): prevS1(prevS1), prevS2(prevS2), used(used) {};
};

int** LCS;
trace** Backtracking;

int main()
{
    int l1, l2;
    string S1, S2;
    cin >> S1 >> S2;
    
    l1 = S1.length();
    l2 = S2.length();
    
    LCS = new int*[l1];
    Backtracking = new trace*[l1];
    for (int i = 0; i < l1; i++) {
        LCS[i] = new int[l2]{};
        Backtracking[i] = new trace[l2]{};
    }
    
    LCS[0][0] = S1[0] == S2[0];
    Backtracking[0][0] = trace(0, 0, (LCS[0][0]));
    
    //initialize 0th column
    for (int b = 1; b < l2; b++) {
        //use S2[b]
        if (S1[0] == S2[b]) {
            LCS[0][b] = 1;
            Backtracking[0][b] = trace(0, b, true);
        }
        //can't use S2[b]
        else {
            LCS[0][b] = LCS[0][b - 1];
            Backtracking[0][b] = trace(0, b - 1, false);
        }
    }
    //initialize 0th row
    for (int a = 1; a < l1; a++) {
        //use S1[a]
        if (S1[a] == S2[0]) {
            LCS[a][0] = 1;
            Backtracking[a][0] = trace(a, 0, true);
        }
        //can't use S1[a]
        else {
            LCS[a][0] = LCS[a - 1][0];
            Backtracking[a][0] = trace(a - 1, 0, false);
        }
    }
    
    for (int a = 1; a < l1; a++) {
        for (int b = 1; b < l2; b++) {
            //first, initialize with "useless S1[a]" case.
            LCS[a][b] = LCS[a - 1][b];
            Backtracking[a][b] = trace(a - 1, b, false);
        
            //second, compare it with "useless S2[b]" case and save better one.
            if (LCS[a][b] < LCS[a][b - 1]) {
                LCS[a][b] = LCS[a][b - 1];
                Backtracking[a][b] = trace(a, b - 1, false);
            }
        
            //lastly, if we can use S1 and S2, compare it with best "none using" case and save better one.
            if (S1[a] == S2[b] && LCS[a][b] < LCS[a - 1][b - 1] + 1) {
                LCS[a][b] = LCS[a - 1][b - 1] + 1;
                Backtracking[a][b] = trace(a - 1, b - 1, true);
            }
        }
    }
    
    
    cout << LCS[l1 - 1][l2 - 1] << "\n";
    
    int a = l1 - 1, b = l2 - 1;
    string reversedAnswer;
    if (LCS[l1 - 1][l2 - 1]) {
        while (LCS[a][b] != 1 || !Backtracking[a][b].used) {
            trace cur = Backtracking[a][b];
            if (cur.used) 
                reversedAnswer += S1[a];
            a = cur.prevS1;
            b = cur.prevS2;
        }
        reversedAnswer += S1[a];
        for (auto it = reversedAnswer.rbegin(); it != reversedAnswer.rend(); it++) {
            cout << *it;
        }
    }
   
   return 0;
}
