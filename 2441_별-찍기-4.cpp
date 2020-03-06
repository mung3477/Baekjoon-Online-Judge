#include <iostream>
using namespace std;

int main(void)
{
    int N, i;
    cin>>N;

    //repeat N times
    //T: the number of stars, N - T: the number of blanks
    for(int T = N; T > 0; T--) {
        for(int j = N - T; j > 0; j--) {
            cout<<" ";
        }
        for(int k = T; k > 0; k--) {
            cout<<"*";
        }
        cout<<endl;
    }
}