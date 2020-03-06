#include <iostream>
using namespace std;

int main(void)
{
    char c;
    while(1) {
        for(int i = 0; i < 10; i++) {
            cin>>c;
            if(cin.eof()) break;
            else cout<<c;
        }
        if(cin.eof()) break;
        cout<<endl;
    }
}