#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

long long my_min(long long a, long long b)
{
    if (a < b)
        return (a);
    else
        return (b);
}

int my_max(int a, int b)
{
    if (a < b)
        return (b);
    else
        return (a);
}

int my_max3(int a, int b, int c)
{
    return (my_max(my_max(a, b), c));
}

int *make_primes(int *p_primes_size)
{
    int         is_prime[MAX + 1] = {0, };
    int         *prime;
    long long   i;
    long long   j;

    i = 1;
    while (++i <= MAX)
        is_prime[i] = 1;

    i = 1;
    while (++i <= MAX)
        if (is_prime[i])
        {
            j = i;
            while (i * j <= MAX)
            {
                is_prime[i * j] = 0;
                j += 1;
            }
        }
    i = 1;
    while (++i <= MAX)
        *p_primes_size += is_prime[i];
    prime = (int *)malloc(sizeof(int) * (*p_primes_size));
    i = 1;
    j = 0;
    while (++i <= MAX)
        if (is_prime[i])
            prime[j++] = i;
    return (prime);
}

void    factorize(int num, int *factorized, int *primes, int primes_size)
{
    int i;

    i = -1;
    while (++i < primes_size)
    {
        while (num % primes[i] == 0)
        {
            num /= primes[i];
            factorized[i] += 1;
        }
    }
}

int LCM(int *a, int *b, int *c, int *primes, int primes_size)
{
    int i;
    int res;

    i = -1;
    res = 1;
    while (++i < primes_size)
        if (a[i] || b[i] || c[i])
            res = res * round(pow(primes[i], my_max3(a[i], b[i], c[i])));
    return (res);
}

int main(void)
{
    int i;
    int j;
    int k;
    long long ans;
    int numbs[5];
    int *factorized[5];
    int primes_size;
    int *primes;

    i = -1;
    primes_size = 0;
    primes = make_primes(&primes_size);
    while (++i < 5)
    {
        scanf("%d", &numbs[i]);
        factorized[i] = (int *)malloc(sizeof(int) * primes_size);
        j = -1;
        while (++j < primes_size)
            factorized[i][j] = 0;
    }

    i = -1;
    while (++i < 5)
        factorize(numbs[i], factorized[i], primes, primes_size);

    i = -1;
    ans = 10000000000;
    while (++i < 3)
    {
        j = i;
        while (++j < 4)
        {
            k = j;
            while (++k < 5)
            ans = my_min(ans, LCM(factorized[i], factorized[j], factorized[k], primes, primes_size));
        }
    }
    printf("%d", ans);

    i = -1;
    while (++i < 5)
        free(factorized[i]);
    free(primes);
    return (0);
}