#include "main.h"

/**
 * read_flags - compute active flags
 * @format: the formatted string which to print
 * @k: take the parameter.
 * Return: Flags:
 */
int read_flags(const char *format, int *k)
{
	int m, curr_k = *k + 1;
	int flags = 0;
	const char FLAGS_CHAR[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARRAY[] = {MINUS, PLUS, ZERO, HASH, SPACE, 0};

	while (format[curr_k] != '\0')
	{
		for (m = 0; FLAGS_CHAR[m] != '\0'; m++)
		{
			if (format[curr_k] == FLAGS_CHAR[m])
			{
				flags |= FLAGS_ARRAY[m];
				break;
			}
		}

		if (FLAGS_CHAR[m] == 0)
			break;

		curr_k++;
	}

	*k = curr_k - 1;

	return (flags);
}
