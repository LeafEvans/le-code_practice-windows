#include <stdio.h>

long long Function(long long n)
{
    long long a = 1;
    long long b = 1;
    long long c = 1;
    long long d = 1;

    while (n > 3)
    {
        d = 2 * c + 3 * b + 5 * a;
        a = b;
        b = c;
        c = d;
        n--;
    }

    return d;
}

int main(void)
{
    int n = 0;
    long long num = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &num);
        printf("%lld\n", Function(num));
    }

    return 0;
}