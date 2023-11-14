#include "main.h"

/**
 * print_pointer - prints the value of a pointet.
 * @types: List of arguments
 * @buff: Buff array to help print
 * @flags: compute active flags
 * @width: read width
 * @precision: Precision conditions
 * @size: Size conditions
 * Return: Number of chars to print
 */
int print_pointer(va_list types, char buff[],
		int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int index = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buff[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	for (; num_addrs > 0; num_addrs /= 16, length++)
	{
		buff[index--] = map_to[num_addrs % 16];
	}
	if ((flags & ZERO) && !(flags & MINUS))
		padd = '0';
	if (flags & PLUS)
		extra_c = '+', length++;
	else if (flags & SPACE)
		extra_c = ' ', length++;

	index++;
	return (write_pointer(buff, index, length,
				width, flags, padd, extra_c, padd_start));
}

/**
 * display_non_printable - prints codes in hexa of non printable chars
 * @types: List of arguments
 * @buff: Buff array to help print
 * @flags: computes active flags
 * @width: read width
 * @precision: Precision condition
 * @size: Size condition
 * Return: Number of chars to print
 */
int display_non_printable(va_list types, char buff[],
		int flags, int width, int precision, int size)
{
	int i = 0, order = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	for (; str[i] != '\0'; i++)
	{
		if (check_printable(str[i]))
			buff[i + order] = str[i];
		else
			order += display_hexa_code(str[i], buff, i + order);
	}

	buff[i + order] = '\0';

	return (write(1, buff, i + order));
}
/**
 * print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @buff: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buff[],
		int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buff);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - print a string in rot13.
 * @types: List of arguments
 * @buff: Buff array to print
 * @flags: computes active flags
 * @width: read width
 * @precision: Precision condition
 * @size: Size condition
 * Return: numbers of chars to print
 */
int print_rot13string(va_list types, char buff[],
		int flags, int width, int precision, int size)
{
	char n;
	char *str;
	unsigned int i = 0, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buff);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	while (str[i])
	{
		j = 0;
		while (in[j])
		{
			if (in[j] == str[i])
			{
				n = out[j];
				write(1, &n, 1);
				count++;
				break;
			}
			j++;
		}
		if (!in[j])
		{
			n = str[i];
			write(1, &n, 1);
			count++;
		}
		i++;
	}
	return (count);
}
