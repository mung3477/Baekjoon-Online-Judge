#include <iostream>
using namespace std;

int main(void)
{
    int N;
    cin>>N;

    long pact[13];
    pact[0] = 1;
    pact[1] = 1;
    for(int i = 2; i <= 12; i++) {
        pact[i] = pact[i - 1] * (long)i;
    }

    cout<<pact[N];

}