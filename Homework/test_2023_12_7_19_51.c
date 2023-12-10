#include <stdio.h>
#include <string.h>

double calculator(char *ptr)
{
    char op = 0;
    double num1 = 0.0;
    double num2 = 0.0;
    if (sscanf(ptr, "%lf%c%lf", &num1, &op, &num2) != 3)
    {
        printf("Input Error\n");
        return 0.0;
    }
    switch (op)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        if (num2 == 0)
        {
            printf("Input Error\n");
            return 0.0;
        }
        return num1 / num2;
    default:
        printf("Input Error\n");
        return 0.0;
    }
}

int main()
{
    char input[20] = {0};
    fgets(input, sizeof(input), stdin);
    input[strlen(input) - 1] = '\0';
    double result = calculator(input);
    if (result != 0.0)
    {
        printf("%.2lf\n", result);
    }
    return 0;
}