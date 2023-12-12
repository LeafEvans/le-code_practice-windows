#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isRight(char* str, int len)
{
	int num = 0;

	if (len > 3)
	{
		return 0;
	}

	while (len)
	{
		if (isdigit(*(str + len - 1)))
		{
			num += num * 10 + *(str + len - 1) - '0';
			len--;
		}
		else
		{
			return 0;
		}
	}

	if (num >= 0 && num <= 255)
	{
		return 1;
	}

	return 0;
}

int main(void)
{
	int n = 0;
	char str[101] = { 0 };
	char str1[101] = { 0 };
	char str2[101] = { 0 };
	char str3[101] = { 0 };
	char str4[101] = { 0 };
	char* ptr[4] = { str1, str2, str3, str4 };

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int flag = 1;
		fgets(str, 101, stdin);
		str[strlen(str) - 1] = '\0';
		sscanf(str, "%s:%s:%s:%s", str1, str2, str3, str4);

		for (int j = 0; j < 4; j++)
		{
			if (isRight(ptr[i], strlen(ptr[i]) == 0))
			{
				flag = 0;
			}
		}

		if (flag == 1)
		{
			printf("yes\n");
		}
		else
		{
			printf("no\n");
		}
	}

	return 0;
}