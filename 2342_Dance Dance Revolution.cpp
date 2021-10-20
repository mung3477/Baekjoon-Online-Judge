#include <iostream>
#include <vector>
#include <cmath>
#include <typeinfo>
#define MAX 500000
using std::cin;
using std::cout;
using std::vector;
using std::abs;

int moveFoot[5][5];     //[from][to]

void fillMoveFoot() {
    //0 -> other
    for (int i = 1; i <= 4; i++) {
        moveFoot[0][i] = 2;
        moveFoot[i][0] = MAX;   //prohibit
    }
        
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (i == j) moveFoot[i][j] = 1;
            else if (abs(i - j) == 2) moveFoot[i][j] = 4;
            else moveFoot[i][j] = 3;
        }
    }
}

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int main()
{
    fillMoveFoot();
    int N, ans = MAX;
    /*
        DP[i][0 ~ 4][0 ~ 4] : vector[i]를 왼/오른발로 밟았을 때 반대 발 위치를 만들 수 있는 최소 cost
        2nd index: 왼발의 위치
        3rd index: 오른발의 위치
    */
    int*** DP;             
    vector<int> command;
    
    while (1) {
        int input;
        cin >> input;
        if (input == 0) break;
        command.push_back(input);
    }
    
    N = command.size();
    DP = new int**[N];
    for (int i = 0; i < N; i++) {
        DP[i] = new int*[5];
        for (int j = 0; j < 5; j++) 
            DP[i][j] = new int[5]{MAX, MAX, MAX, MAX, MAX};
    }

    DP[0][command.at(0)][0] = 2;    //using left foot
    DP[0][0][command.at(0)] = 2;    //using right foot
    
    for (int i = 1; i < N; i++) {
        int target = command.at(i);
        
        for (int k = 0; k <= 4; k++) {
            //이동 후 두 발이 같은 칸에 있는 경우는 없음.
            if (target != k) {
                //using left foot
                for (int l = 0; l <= 4; l++) 
                    //두 발이 같은 칸에 있는 경우에서 이동해 올 수 없음.
                    if (l != k) DP[i][target][k] = min(DP[i][target][k], DP[i - 1][l][k] + moveFoot[l][target]);
                    
                //using right foot
                for (int r = 0; r <= 4; r++) 
                    ////두 발이 같은 칸에 있는 경우에서 이동해 올 수 없음.
                    if (r != k) DP[i][k][target] = min(DP[i][k][target], DP[i - 1][k][r] + moveFoot[r][target]);
            }
        }
    }
    
    int last = command.back();
    for (int l = 0; l <= 4; l++) {
        ans = min(ans, DP[N - 1][l][last]);    
    }
    for (int r = 0; r <= 4; r++) {
        ans = min(ans, DP[N - 1][last][r]);
    }
    
    cout << ans;
    
    return 0;
}
