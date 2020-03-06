#include <iostream>
#include <stdio.h>
using namespace std;

int main(void)
{
    int N, ans = 0;
    cin>>N;
    getchar();
    for(N; N > 0; N--) {
        ans += (int)(getchar() - '0');
    }
    cout<<ans;
}