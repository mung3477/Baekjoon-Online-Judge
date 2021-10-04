#include <iostream>
using std::cin;
using std::cout;

int stair[101][10][10][1024]; //start: 0, 10 // end: 0, 10 

//뒤에 숫자 하나 붙이기
void extend(int i, int j, int k, int used) {
    long long current = stair[i][j][k][used];
    
    //뒤, 숫자 1 감소
    if (k != 0)
        stair[i + 1][j][k - 1][used | 1 << k - 1] = (stair[i + 1][j][k - 1][used | 1 << k - 1] + current) % 1000000000;
    
    //뒤, 숫자 1 증가
    if (k != 9)
        stair[i + 1][j][k + 1][used | 1 << k + 1] = (stair[i + 1][j][k + 1][used | 1 << k + 1] + current) % 1000000000;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, next, allUsed = 0b1111111111;
    long long total = 0;
    cin >> N;
    
    for (int j = 1; j <= 9; j++) {
        stair[1][j][j][1 << j]= 1;
    }
   
    //length
    for (int i = 1; i <= N - 1; i++) {
        //start
        for (int j = 1; j <= 9; j++) {
            //end
            for (int k = 0; k <= 9; k++) {
                for (int used = 0; used <= allUsed; used++)
                    if (stair[i][j][k][used]) extend(i, j, k, used);
            }
        }
    }
    
    for (int j = 1; j <= 9; j++) {
        for (int k = 0; k <= 9; k++) {
            total = ((long long)total + stair[N][j][k][allUsed]) % 1000000000;
        }
    }
    
    cout << total;
    
    return 0;
}
