#include "main.h"

/**
 * read_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @k: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int read_width(const char *format, int *k, va_list list)
{
	int curr_k = *k + 1;
	int width = 0;

	while (format[curr_k] != '\0')
	{
		if (check_digit(format[curr_k]))
		{
			width *= 10;
			width += format[curr_k] - '0';
		}
		else if (format[curr_k] == '*')
		{
			curr_k++;
			width = va_arg(list, int);
			break;
		}
		else
		{
			break;
		}
		curr_k++;
	}
	*k = curr_k - 1;
	return (width);
}
