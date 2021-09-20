#include <iostream>
using std::cin;
using std::cout;

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, K;
    int** item;             //[0]: 무게, [1]: 가치
    int** maxValue;         //[i][j] : i번째 물건까지 사용해서 최대 j만큼의 무게를 들 수 있을 때의 가치 최댓값
    
    cin >> N >> K;
    item = new int*[N + 1];
    maxValue = new int*[N + 1];
    for (int i = 0; i <= N; i++) {
        item[i] = new int[2]{};
        if (i > 0) cin >> item[i][0] >> item[i][1];
        
        maxValue[i] = new int[K + 1]{};
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= K; j++) {
            
            maxValue[i][j] = (
                j >= item[i][0] 
                ? max(maxValue[i - 1][j], maxValue[i - 1][j - item[i][0]] + item[i][1])
                : maxValue[i - 1][j]
            );
        }
    }
    
    cout << maxValue[N][K];
    
    return 0;
}
