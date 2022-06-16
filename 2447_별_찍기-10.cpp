#include <stdlib.h>
#include <iostream>
#include <math.h>

void    compose(char *P, int P_size, int k, int row, int col);
void    copy(char *P, int P_size, int k, int row, int col);
void    print(char *P, int P_size);
void    print_base(void);

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int     N;
    int     k;
    int     P_size;
    char    *P;

    std::cin >> N;
    if (N == 3)
        print_base();
    else
    {
        P_size = N / 3;
        P = (char *)malloc(sizeof(char) * P_size * P_size);
        if (!P)
            return (1);
        for (int i = 0; i < P_size; i++)
            for (int j = 0; j < P_size; j++)
                P[P_size * i + j] = ' ';
        compose(P, P_size, std::log2(P_size) / std::log2(3), 0, 0);
        /* for (int i = 0; i < P_size; i++)
        {  
            if (i)
                std::cout << '\n';
            for (int j = 0; j < P_size; j++)
                std::cout << P[i * P_size + j];
        } */
        print(P, P_size);
        free(P);
    }
    return (0);
}

void    compose(char *P, int P_size, int k, int row, int col)
{
    const int   prev_size = (int)std::pow(3, k - 1);
    if (k == 1)
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (!(i == 1 && j == 1))
                    P[P_size * (row + i) + (col + j)] = '*';
    }
    else
    {
        compose(P, P_size, k - 1, row, col);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (!(i == 1 && j == 1))
                    copy(P, P_size, k - 1, prev_size * i, prev_size * j);
    }
}

/*
    Copy Pattern's first (3^pow) * (3^pow) pattern to the same size of destination,
    which starts at (row, col).
*/
void    copy(char *P, int P_size, int pow, int row, int col)
{
    const int src_size = (int)std::pow(3, pow);

    for (int i = 0; i < src_size; i++)
        for (int j = 0; j < src_size; j++)
            P[P_size * (row + i) + (col + j)] = P[P_size * i + j];
}

void    print(char *P, int P_size)
{
    for (int repeat = 0; repeat < 3; repeat++)
    {   
        for (int i = 0; i < P_size; i++)
        {
            if (repeat || i)
                std::cout << '\n';
            for (int dup = 0; dup < 3; dup++)
                for (int j = 0; j < P_size; j++)
                    std::cout << (repeat == 1 && dup == 1 ? ' ' : P[i * P_size + j]);
        }
    }
}

void    print_base(void)
{
    for (int i = 0; i < 3; i++)
    {
        if (i)
            std::cout << '\n';
        for (int j = 0; j < 3; j++)
            std::cout << (i == 1 && j == 1 ? ' ' : '*');
    }
}