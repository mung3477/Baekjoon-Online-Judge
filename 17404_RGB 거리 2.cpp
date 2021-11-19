#include <iostream>
#include <limits.h>
using std::cin;
using std::cout;

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int main()
{
    int** cost;
    int*** Start; //cummulative, j번째 색으로 칠할 때 여태까지 소모된 비용

    int N;
    
    cin >> N;
    
    cost = new int*[N + 1];
    Start = new int**[3];
    for (int i = 0; i < 3; i++)
        Start[i] = new int*[N + 1];

    for (int j = 1; j <= N; j++) {
        cost[j] = new int[3]{};
        for (int k = 0; k < 3; k++) {
            cin >> cost[j][k];
        }
            
        for (int i = 0; i < 3; i++) {  
            Start[i][j] = new int[3]{};
        }
    }
    
    //initialize
    for (int i = 0; i < 3; i++) {
        Start[i][1][i] = cost[1][i];
    }
    
    //Start with i
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            if (i == k) 
                Start[i][2][k] = INT_MAX;
            else 
                Start[i][2][k] = Start[i][1][i] + cost[2][k];
        }
    }
        
    for (int j = 3; j <= N; j++) {
        for (int i = 0; i < 3; i++) {
            //Red
            Start[i][j][0] = min(Start[i][j - 1][1], Start[i][j - 1][2]) + cost[j][0];
            //Green
            Start[i][j][1] = min(Start[i][j - 1][0], Start[i][j - 1][2]) + cost[j][1];
            //Blue
            Start[i][j][2] = min(Start[i][j - 1][0], Start[i][j - 1][1]) + cost[j][2];
        }
    }
    
    int result = INT_MAX;
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            if (i == k) continue;
            else result = min(result, Start[i][N][k]);
        }
    }

    cout << result;
    return 0;
}
