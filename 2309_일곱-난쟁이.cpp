#include <cstdio>
#include <algorithm>
using namespace std;

int main(void)
{
    int sum(0);
    int arr[9] = {0, };
    for(int i = 0; i < 9; i++){
        scanf(" %d", arr + i);
        sum += *(arr + i);
    }
    sort(arr, arr + 9);

    int i, j;
    bool stop = false;
    for(i = 0; i < 8; i++){
        for(j = i + 1; j < 9; j++){
            if(sum - arr[i] - arr[j] == 100){
                stop = true;
                break;
            }
        }
        if(stop) break;
    }

    for(int k = 0; k < 9; k++){
        if(k != i && k != j)
            printf("%d\n", arr[k]);
    }

    return 0;
}