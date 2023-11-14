#include "main.h"
/**
 *_print - prints an argument
 * @ft: Formatted string in which to print
 * @list: List of arguments to be print
 * @index: index
 * @buff: buff array to print.
 * @flags: Compute active flags
 * @width: read width.
 * @precision: Precision condition
 * @size: Size conditions
 * Return: 1 or 2;
 */
int _print(const char *ft, int *index, va_list list, char buff[],
	int flags, int width, int precision, int size)
{
	int i, unknw_len = 0, print_chars = -1;
	ft_t ft_types[] = {
		{'c', print_char}, {'s', display_string}, {'%', display_percent},
		{'i', print_int}, {'d', print_int}, {'b', display_binary},
		{'u', display_unsigned}, {'o', display_octal}, {'x', display_hexadecimal},
		{'X', display_hexa_upper}, {'p', print_pointer}, {'S', display_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; ft_types[i].ft != '\0'; i++)
		if (ft[*index] == ft_types[i].ft)
			return (ft_types[i].fn(list, buff, flags, width, precision, size));

	if (ft_types[i].ft == '\0')
	{
		if (ft[*index] == '\0')
			return (-1);
		unknw_len += write(1, "%%", 1);
		if (ft[*index - 1] == ' ')
			unknw_len += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (ft[*index] != ' ' && ft[*index] != '%')
				--(*index);
			if (ft[*index] == ' ')
				--(*index);
			return (1);
		}
		unknw_len += write(1, &ft[*index], 1);
		return (unknw_len);
	}
	return (print_chars);
}
