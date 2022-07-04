#include <stdio.h>

int count_alpha[256];

int main(void)
{
    char    c;
    int     biggest;
    
    biggest = 0;

    while ((c = getchar()) != EOF)
        count_alpha[c] += 1;
    
    for (int i = 'a'; i <= 'z'; i++)
    {
        if (biggest < count_alpha[i]) 
            biggest = count_alpha[i];
    }

    for (int i = 'a'; i <= 'z'; i++)
        if (biggest == count_alpha[i])
            printf("%c", i);
        
    return (0);
}