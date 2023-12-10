#include <stdio.h>

int max(int *array, int size)
{
    int max = array[0];
    for (int i = 1; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

int nocmp(int *ptr1, int *ptr2)
{
    int max1 = max(ptr1, 10);
    int max2 = max(ptr2, 10);

    if (max1 > max2)
    {
        return max1;
    }
    else
    {
        return max2;
    }
}

int main()
{
    int array1[10];
    int array2[10];

    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &array1[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &array2[i]);
    }

    int result = nocmp(array1, array2);
    printf("%d\n", result);

    return 0;
}