#include <stdio.h>

void print1(void)
{
    printf("\"����Լ��� ������?\"\n");
}

void print2(void)
{
    printf("\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���.\n");
}

void print3(void)
{
    printf("���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���.\n");
}

void print4(void)
{
    printf("���� ���� ��κ� �ǾҴٰ� �ϳ�. �׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"\n");
}

void print5(void)
{
    printf("��� �亯�Ͽ���.\n");
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
        printf("\"����Լ��� �ڱ� �ڽ��� ȣ���ϴ� �Լ����\"\n");
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
    printf("��� �� ��ǻ�Ͱ��а� �л��� ������ �������� ã�ư� ������.\n");
    print(N, 0);

    return 0;
}