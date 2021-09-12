#include <iostream>
#include <string>
#include <stack>
using std::cin;
using std::cout;
using std::string;
using std::stack;

int main()
{
    int i;
    string input;
    string exploder;
    string answer;
    stack<char> result;
    stack<char> temp;
    
    cin >> input >> exploder;
    
    for (char& c : input) {
       result.push(c);
       
        if (c == exploder.back()) {
            for (i = exploder.length() - 1; 0 <= i && !result.empty(); i--) {
                if (result.top() == exploder.at(i)) {
                    temp.push(result.top());
                    result.pop();
                }
                else break;
            }
            
            if (i != -1) {
                while (!temp.empty()) {
                    result.push(temp.top());
                    temp.pop();
                }
            }
            
            while (!temp.empty()) { temp.pop(); }
        }
    }
    
    while (!result.empty()) {
        answer += result.top();
        result.pop();
    }
    
    if (answer.empty()) {
        cout << "FRULA";
    }
    else {
        for (i = answer.length() - 1; 0 <= i; i--) {
            cout << answer.at(i);
        }
    }
    
    return 0;
}
