
#include <cstdio>
#include <vector>
using namespace std;

/*
1000 이하의 삼각수를 다 만들어놓고 시작.
주어진 수보다 작은 삼각수 중 가장 큰 수를 포함하는 경우부터 전부 탐색. n^2 + n <= 2000 이면 n = 40정도. 40C3 < 1억
*/

int main(void)
{
    int T;
    scanf(" %d", &T);

    vector<int> triang;

    int temp = 0;
    for(int n = 1; n * (n + 1) / 2 <= 1000; n++){
        temp = n * (n + 1) / 2;
        triang.push_back(temp);
    }

    for(int rep = 1; rep <= T; rep++){
        int K;
        scanf(" %d", &K);
        bool found = false;

        //K보다 작은 가장 큰 삼각수 탐색
        int i = 0;
        while(triang[i] <= K && i < triang.size()){
            i++;
        }
        
        i = i - 1;  //K보다 작은 가장 큰 삼각수를 가리킴


        //삼각수 세 개로 이루어지는 수
        for(i; i >= 0 && !found; i--){
            for(int j = i; j >= 0 && !found; j--){
                for(int s = j; s >= 0 && !found; s--){
                    if(triang[i] + triang[j] + triang[s] == K){
                        found = true;
                    }
                }
            }    
        }
        

        if(found){
            printf("1\n");
        }
        else{
            printf("0\n");
        }
    }
}