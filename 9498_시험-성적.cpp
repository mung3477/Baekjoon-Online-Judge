#include <iostream>
using namespace std;

int main(void)
{
    int N;
    cin>>N;

    if(90 <= N && N <= 100) cout<<"A";
    else if (80 <= N) cout<<"B";
    else if (70 <= N) cout<<"C";
    else if (60 <= N) cout<<"D";
    else cout<<"F";
}