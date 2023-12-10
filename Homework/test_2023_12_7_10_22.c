#include <stdio.h>
#include <string.h>

int main(void)
{
    // char arr[] = "abcdef"; // abcdef\0
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int len = strlen(arr);

    printf("%u\n", len);

    return 0;
}
