#include <assert.h>
#include <stdio.h>
#include <string.h>

void *myMemmove(void *dest, void *src, size_t num)
{
    assert(dest && src);
    void *ret = dest;
    if (dest < src)
    {
        while (num--) // 与memcpy一致
        {
            *(char *)dest = *(char *)src;
            dest = (char *)dest + 1;
            src = (char *)src + 1;
        }
        return ret;
    }
    else
    {
        while (num--) // num判断后--，只剩num-1个字节
        {
            *((char *)dest + num) = *((char *)src + num); // 跳过num-1个字节后就时指向目标数据的最后一个字节，然后解引用赋值
        }                                                 //之后num再--，就可以实现
        return ret;
    }
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    myMemmove(arr, arr + 2, 20);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}