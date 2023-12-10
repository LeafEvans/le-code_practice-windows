#include <stdio.h>
#include <string.h>
#include <assert.h>

void *myMemcpy(void *dest, const void *src, size_t num)
{
    assert(dest && src);
    void *ret = dest;
    while (num--)
    {
        *(char *)dest = *(char *)src;
        dest = (char *)dest + 1;
        src = (char *)src + 1;
    }
    return ret;
}

int main(void)
{
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8 , 9, 10};
    int arr2[10] = {0};

    myMemcpy(arr1 + 2, arr1, 28);
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", arr1[i]);
    }

    return 0;
}