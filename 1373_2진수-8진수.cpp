#include <iostream>
#include <string>
using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    string input, output;
    cin >> input;

    if(input == "0"){
        cout << input;
        return 0;
    }

    string::reverse_iterator ri = input.rbegin();
    int loop = 1, n = 0;
    while(ri != input.rend()){
        n += (*ri - '0') << (loop - 1);

        if(loop == 3){
            output += n + '0';
            n = 0;
            loop = 0;
        }
        loop++;
        ri++;
    }
    if(n){
        output += n + '0';
    }
    
    for(ri = output.rbegin(); ri != output.rend(); ri++){
        cout<<*ri;
    }
    return 0;
}