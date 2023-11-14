#include "main.h"

/**
 * print_char - prints a char
 * @types: List of arguments
 * @buff: Buff array to handle print
 * @flags: computes active flags
 * @width: Width
 * @precision: Precision conidition
 * @size: Size condition
 * Return: Number of chars to print
 */
int print_char(va_list types, char buff[],
		int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (write_char(c, buff, flags, width, precision, size));
}
/**
 * display_string - display string
 * @types: list of arguments
 * @buff: Buff array to display
 * @flags: Computes active flags
 * @width: read width.
 * @precision: precision condition
 * @size: Size specifier
 * Return: number of chars to display
 */
int display_string(va_list types, char buff[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buff);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/**
 * display_percent - display percent sign
 * @types: list of arguments
 * @buff: Buff array to help display
 * @flags: computes active flags
 * @width: read width.
 * @precision: Precision condition
 * @size: Size condition
 * Return: number of chars to display
 */
int display_percent(va_list types, char buff[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buff);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - print an int
 * @types: list of arguments
 * @buff: Buff array to handle print
 * @flags: computes active flags
 * @width: read width.
 * @precision: Precision condition
 * @size: Size condition
 * Return: Number of chars to print
 */
int print_int(va_list types, char buff[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n =change_size_number(n, size);

	if (n == 0)
		buff[i--] = '0';

	buff[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buff[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buff, flags, width, precision, size));
}
/**
 * display_binary - display an unsigned number
 * @types: List of arguments
 * @buff: Buff array to help display
 * @flags: computes active flags
 * @width: read width.
 * @precision: Precision condition
 * @size: Size condition
 * Return: Numbers of char to display
 */
int display_binary(va_list types, char buff[],
		int flags, int width, int precision, int size)
{
	unsigned int x, y, i, sum;
	unsigned int b[32];
	int count;

	UNUSED(buff);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	y = 2147483648;
	b[0] = x / y;
	for (i = 1; i < 32; i++)
	{
		y /= 2;
		b[i] = (x / y) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += b[i];
		if (sum || i == 31)
		{
			char k = '0' + b[i];

			write(1, &k, 1);
			count++;
		}
	}
	return (count);
}
