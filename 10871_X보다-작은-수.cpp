#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
    int N, X;
    cin>>N>>X;
    vector<int> vec(N);
    for(int i = 0; i < N; i++) {
        cin>>vec[i];
    }
    for(int i = 0; i < N; i++) {
        if(vec[i] < X) {
            cout<<vec[i]<<" ";
        }
    }
}