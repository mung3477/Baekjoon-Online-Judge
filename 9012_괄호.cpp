#include <stdio.h>
#include <stack>
#include <stdbool.h>
using namespace std;

void clearBuffer() {
    char c;
    while((c = getchar()) != '\n') {}
}

bool checkVPS(void)
{
    stack<char> s;
    char c;
    bool ans = true;;
    while((c = getchar()) != '\n') {
        if(c == '(') { s.push(c); }
        else {
            if(s.empty()) {
                ans = false;
                clearBuffer();
                break;
            }
            else s.pop();
        }
    }
    return (ans && s.empty());
}

int main(void)
{
    int T;
    scanf("%d\n", &T);

    for(int i = 1; i <= T; i++){
        if(checkVPS()) { printf("YES\n"); }
        else { printf("NO\n"); }
    }
}
