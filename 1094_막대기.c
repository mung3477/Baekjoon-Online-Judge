#include <stdio.h>

int sum_of_sticks(int *sticks, int stick_num)
{
    int sum;

    sum = 0;
    for (int i = 0; i < stick_num; i++)
        sum += sticks[i];
    return (sum);
}

int main(void)
{
    int sticks[7] = {64, };
    int stick_num, X;

    stick_num = 1;
    scanf("%d", &X);

    while (X < sum_of_sticks(sticks, stick_num))
    {
        sticks[stick_num] = sticks[stick_num - 1] / 2;
        sticks[stick_num - 1] = sticks[stick_num];
        stick_num += 1;

        if (X <= sum_of_sticks(sticks, stick_num - 1))
        {
            sticks[stick_num - 1] = 0;
            stick_num -= 1;
        }
    }

    printf("%d", stick_num);
    return (0);
}