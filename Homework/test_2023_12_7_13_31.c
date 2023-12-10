#include <stdio.h>
#include <string.h>
#include <assert.h>

char *myStrcpy(char *dest, const char *src)
{
    char *original_dest = dest;
    assert(src || dest);
    while (*dest++ = *src++)
    {
        ;
    }
    return original_dest;
}

int main(void)
{
    char name[20] = {0};
    myStrcpy(name, "zhangshan");
    printf("%s\n", name);
    return 0;
}