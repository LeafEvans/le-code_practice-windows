#include <stdio.h>

int *findMax(int arr[], int len)
{
    int *max = arr[0];

    for (int i = 0; i < len; i++)
    {
        if (arr[i] > max)
        {
            max = &arr[i];
        }
    }

    return max;
}

int nocmp(int *ptr1, int *ptr2)
{
    return (*ptr1 > *ptr2) ? *ptr1 : *ptr2;
}

int main(void)
{

    return 0;
}