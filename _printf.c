#include "main.h"

void print_buff(char buff[], int *buff_index);

/**
 * _printf - printf the function
 * @format: the format.
 * Return: prine chars.
 */
int _printf(const char *format, ...)
{
	int i, print = 0, print_chars = 0;
	int flags, width, precision, size, buff_index = 0;
	va_list list;
	char buff[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		switch (format[i])
		{
			case '%':
				print_buff(buff, &buff_index);
				flags = read_flags(format, &i);
				width = read_width(format, &i, list);
				precision = read_precision(format, &i, list);
				size = read_size(format, &i);
				++i;
				print = _print(format, &i, list, buff,
						flags, width, precision, size);
				if (print == -1)
					return (-1);
				print_chars += print;
				break;
			default:
				buff[buff_index++] = format[i];
				if (buff_index == BUFF_SIZE)
					print_buff(buff, &buff_index);
				print_chars++;
				break;
		}
	}

	print_buff(buff, &buff_index);
	va_end(list);
	return (print_chars);
}

/**
 * print_buff - prints the contents of the buff
 * @buff: array of chars
 * @buff_index: index at which the next char, represents the length.
 */
void print_buff(char buff[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buff[0], *buff_index);
	*buff_index = 0;
}
