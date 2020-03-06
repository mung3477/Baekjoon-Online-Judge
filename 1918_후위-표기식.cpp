#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;

int main(void)
{
    char c;
    char op[7] = "()+-*/";
    stack<char> s;
    //스택이 비어있으면 일단 push
    //top보다 우선순위가 낮은게 들어오면 pop하고 push
    //top보다 우선순위가 높은게 들어오면 push
    //( 는 그냥 push, )는 ( 나올때까지 pop해서 출력
    while(((c = getchar()) != EOF) && (c != '\n')){

        //연산자인 경우
        if(strchr(op, c)) {

            //스택 비어있으면 들어가려는 연산자가 우선순위 1등
            if(s.empty()) {
                s.push(c);
            }

            else{
                switch(c){
                    case '(':
                        s.push(c);
                        break;
                    case ')':
                        while(s.top() != '(') {
                            printf("%c", s.top());
                            s.pop();
                        }
                        s.pop();
                        break;
                    case '+':
                    case '-':
                        while(!s.empty() && (s.top() != '(')) {
                            printf("%c", s.top());
                            s.pop();
                        }
                        s.push(c);
                        break;
                    case '*':
                    case '/':
                        if((s.top() == '*') || (s.top() == '/')){
                            printf("%c", s.top());
                            s.pop();
                        }
                        s.push(c);
                        break;
                }
            }
        }
        //피연산자인 경우
        else printf("%c", c);
    }
    //남았는데 끝난 경우
    while(!s.empty()) { 
        printf("%c", s.top());
        s.pop();
    }
    return 0;
}