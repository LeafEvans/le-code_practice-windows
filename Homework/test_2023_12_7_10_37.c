#include <stdio.h>
#include <assert.h>

size_t myStrlenA(const char *str)
{
    size_t count = 0;
    assert(str);
    while (*str != '\0')
    {
        count++;
        str++;
    }
    return count;
}

size_t myStrlenB(const char *str)
{
    assert(str);
    char *str_n = (char *)str;
    while (*str_n != '\0')
    {
        str_n++;
    }
    return (size_t)(str_n - str);
}

size_t myStrlenC(const char *str)
{
    assert(str);
    if (*str == '\0')
        return 0;
    else
        return 1 + myStrlenC(str + 1);
}

int main(void)
{
    char arr[] = "abcdef"; // abcdef\0
    int len = myStrlenC(arr);

    printf("%u\n", len);

    return 0;
}