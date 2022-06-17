#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime[1000001];

int my_compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int arr_size(int *arr)
{
    int i;

    i = 0;
    while (arr[i])
        i += 1;
    return (i);
}

int my_max(int a, int b)
{
    if (a < b)
        return (b);
    else
        return (a);
}

int *make_primes(void)
{
    long long   i;
    long long   j;
    int         primes_size;
    int         *primes;

    i = 1;
    while (++i <= 1000000)
        is_prime[i] = 1;
    primes_size = 0;
    i = 1;
    while (++i <= 1000000)
    {
        if (is_prime[i])
        {
            j = i;
            while (i * j <= 1000000)
            {
                is_prime[i * j] = 0;
                j += 1;
            }
        }
    }

    i = 1;
    while (++i <= 1000000)
        if (is_prime[i])
            primes_size += 1;
    primes = (int *)malloc(sizeof(int) * (primes_size + 1));
    i = 1;
    j = 0;
    while (++i <= 1000000)
        if (is_prime[i])
            primes[j++] = i;
    primes[primes_size] = 0;
    return (primes);
}

void    find_LCM(int *factors, int *primes)
{
    int i;
    int j;
    int cur;
    int exp;
    int answer;
    int LCM_size;
    int factors_size;
    int smallest_factor;
    int *LCM;

    LCM_size = arr_size(primes);
    smallest_factor = 0;
    LCM = (int *)malloc(sizeof(int) * (LCM_size + 1));
    i = -1;
    while (++i <= LCM_size)
        LCM[i] = 0;
    
    i = -1;
    while (factors[++i])
    {
        cur = factors[i];
        j = -1;
        while (primes[++j])
        {
            exp = 0;
            while (cur % primes[j] == 0)
            {
                cur /= primes[j];
                exp += 1;

                if (!smallest_factor)
                    smallest_factor = primes[j];
            }
            LCM[j] = my_max(LCM[j], exp);
        }
    }

    answer = 1;
    factors_size = i;
    i = -1;
    while (++i < LCM_size)
        if (LCM[i])
            answer = answer * round(pow(primes[i], LCM[i]));

    if (answer == factors[factors_size - 1])
        answer *= smallest_factor;
    printf("%d", answer);
    free(LCM);
}

int main(void)
{
    int n;
    int i;
    int factors[51] = {0, };
    int *primes;

    primes = make_primes();
    scanf("%d", &n);
    i = 0;
    while (i < n)
        scanf("%d", &factors[i++]);
    qsort(factors, n, sizeof(int), my_compare);
    find_LCM(factors, primes);
    free(primes);
}