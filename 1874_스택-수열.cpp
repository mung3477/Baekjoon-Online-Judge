#include <stdio.h>
#include <stack>
using namespace std;

int main(void)
{
    int n;
    scanf("%d", &n);

    //next: 다음에 들어갈 수
    //top: 현재 스택 맨 위인 수
    int next = 1;
    int top = 0;
    stack<int> k;
    char op[1000000];
    int index = 0;

    for(int i = 1; i <= n; i++){
        int t;
        scanf(" %d", &t);

        if(t > top){
            if(next <= t){
                while(next < t + 1) {
                    k.push(next++);
                    op[index++] = '+';
                }
                k.pop();
                op[index++] = '-';
                if(k.empty()) top = 0;
                else top = k.top();
            }
            else{
                printf("NO");
                return 0;
            }
        }

        else if(t == top){
            k.pop();
            op[index++] = '-';
            if(k.empty()) top = 0;
            else top = k.top();
        }
        
        else{
            printf("NO");
            return 0;
        }
    }
    op[index] = '\0';
    for(int i = 0; op[i]; i++){
        printf("%c\n", op[i]);
    }
    return 0;

}