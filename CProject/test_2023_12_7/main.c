#include <stdio.h>
#include <assert.h>

size_t myStrlen(const char *str)
{
    size_t count = 0;
    assert(str);

    while (*str != '\0')
    {
        ++str;
        ++count;
    }

    return count;
}

int main(void)
{
    char a[] = "abcdefg";
    printf("%u", myStrlen(a));
    return 0;
}
