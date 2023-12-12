#include <stdio.h>

void printTriangle(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = n - i; j > 0; j--)
        {
            printf("  ");
        }
        for (int j = n - i; j < n; j++)
        {
            printf("* ");
        }
        printf("\n");
    }
}

int main(void)
{
    int n = 0;
    while (scanf("%d", &n))
    {
        printTriangle(n);
    }

    return 0;
}