#include <iostream>
using namespace std;

int main(void)
{
    int F[10001] = {0, };
    for(int i = 1; i <= 10000; i++) {
        F[i] = F[i - 1] + i;
    }

    int N;
    cin>>N;
    cout<<F[N];
}