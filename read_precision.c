#include "main.h"

/**
 * read_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @k: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int read_precision(const char *format, int *k, va_list list)
{
	int curr_k = *k + 1;
	int precision = -1;

	while (format[curr_k] == '.')
	{
		precision = 0;
		curr_k++;
		while (format[curr_k] != '\0')
		{
			if (check_digit(format[curr_k]))
			{
				precision *= 10;
				precision += format[curr_k] - '0';
			}
			else if (format[curr_k] == '*')
			{
				curr_k++;
				precision = va_arg(list, int);
				break;
			}
			else
			{
				break;
			}
			curr_k++;
		}
	}
	*k = curr_k - 1;
	return (precision);
}
