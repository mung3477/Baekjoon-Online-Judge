#include <cstdio>
#include <vector>
using namespace std;

int main(void)
{
    int N, K, t, coins, val = 0, count = 0;
    vector<int> v;

    scanf(" %d %d", &N, &K);
    
    for(int i = 0; i < N; i++){
        scanf(" %d", &t);
        v.push_back(t);
    }

    //K이하 중 가장 가치가 큰 동전으로 itrator를 옮김
    vector<int>::iterator it_v = v.begin();
    while(*it_v <= K && it_v < v.end()){
        it_v++;
    }
    if(it_v != v.begin())
        it_v--;

    
    while(val != K){
        coins = (K - val) / *it_v;
        val += coins * (*it_v);
        count += coins;

        if(it_v != v.begin())
            it_v--;
    }

    printf("%d", count);
    return 0;
}