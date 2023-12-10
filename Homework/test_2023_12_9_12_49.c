#include <stdio.h>
#include <string.h>
#include <assert.h>

char *myStrncpy(char *dest, const char *src, size_t num)
{
    size_t i = 0;

    for (i = 0; i < num && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    while (i < num)
    {
        dest[i] = '\0';
        ++i;
    }

    return dest;
}

char *myStrncat(char *dest, char *src, size_t num)
{
    size_t i = 0;
    size_t dest_len = 0;

    while (dest[dest_len] != '\0') // 找到目标字符串的末尾
    {
        ++dest_len;
    }

    for (i = 0; i < num && src[i] != '\0'; i++) // 当i小于目标长度，并且要追加的字符不为'\0'字符
    {
        dest[dest_len + i] = src[i]; // 追加
    }
    dest[dest_len + i] = '\0'; // 将字符串末尾赋值为'\0'

    return dest; // 返回首元素地址
}

int main(void)
{
    char arr1[20] = "abcdef";
    char arr2[] = "bit";
    myStrncpy(arr1, arr2, 5);
    printf("%s\n", arr1);
    return 0;
}