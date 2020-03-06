#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;

int main(void)
{
    char c;
    char op[7] = "()+-*/";
    stack<char> s;
    //������ ��������� �ϴ� push
    //top���� �켱������ ������ ������ pop�ϰ� push
    //top���� �켱������ ������ ������ push
    //( �� �׳� push, )�� ( ���ö����� pop�ؼ� ���
    while(((c = getchar()) != EOF) && (c != '\n')){

        //�������� ���
        if(strchr(op, c)) {

            //���� ��������� ������ �����ڰ� �켱���� 1��
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
        //�ǿ������� ���
        else printf("%c", c);
    }
    //���Ҵµ� ���� ���
    while(!s.empty()) { 
        printf("%c", s.top());
        s.pop();
    }
    return 0;
}