#include <stdio.h>

void print1(void)
{
    printf("\"재귀함수가 뭔가요?\"\n");
}

void print2(void)
{
    printf("\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.\n");
}

void print3(void)
{
    printf("마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.\n");
}

void print4(void)
{
    printf("그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"\n");
}

void print5(void)
{
    printf("라고 답변하였지.\n");
}

void printBar(int n)
{
    for(int i = 1; i <= n * 4; i++) { printf("_"); }
}

void print(int level, int n)
{
    //base case
    if(level == n) {
        printBar(n);
        print1();
        printBar(n);
        printf("\"재귀함수는 자기 자신을 호출하는 함수라네\"\n");
        printBar(n);
        print5();
    }

    //normal case
    else {
        printBar(n);
        print1();
        printBar(n);
        print2();
        printBar(n);
        print3();
        printBar(n);
        print4();
        print(level, n + 1);
        printBar(n);
        print5();
    }
}

int main(void)
{
    int N;
    scanf("%d", &N);
    printf("어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다.\n");
    print(N, 0);

    return 0;
}