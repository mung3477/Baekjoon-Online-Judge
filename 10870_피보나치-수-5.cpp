#include <iostream>
using namespace std;

int main(void)
{
    int N;
    cin>>N;
    int F[21];
    F[0] = 0;
    F[1] = 1;

    for(int i = 2; i <= 20; i++) {
        F[i] = F[i - 1] + F[i - 2];
    }

    cout<<F[N];
}