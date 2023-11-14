#include "main.h"

/**
 * display_unsigned - display an unsigned number
 * @types: list of arguments
 * @buff: Buff array to display
 * @flags: computes active flags
 * @width: read width
 * @precision: Precision condition
 * @size: Size condition
 * Return: Number of chars to display
 */
int display_unsigned(va_list types, char buff[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = change_size_unsgnd(num, size);

	if (num == 0)
		buff[i--] = '0';

	buff[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buff[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buff, flags, width, precision, size));
}

/**
 * display_octal - displays an unsigned number in octal notation
 * @types: List of arguments
 * @buff: Buff array to display
 * @flags: compute active flags
 * @width: read width
 * @precision: Precision condition
 * @size: Size condition
 * Return: Number of chars to display
 */
int display_octal(va_list types, char buff[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = change_size_unsgnd(num, size);

	if (num == 0)
		buff[i--] = '0';

	buff[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buff[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & HASH && init_num != 0)
		buff[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buff, flags, width, precision, size));
}

/**
 * display_hexadecimal - displays an unsigned number in hexadecimal notation
 * @types: List of arguments
 * @buff: Buff array to help display
 * @flags: computes active flags
 * @width: read width
 * @precision: Precision condition
 * @size: Size conditon
 * Return: number of chars to display
 */
int display_hexadecimal(va_list types, char buff[],
	int flags, int width, int precision, int size)
{
	return (display_hexa(types, "0123456789abcdef", buff,
		flags, 'x', width, precision, size));
}

/**
 * display_hexa_upper - displays an unsigned number in upper hexadecimal notn.
 * @types: Lista of arguments
 * @buff: Buff array to help display
 * @flags: computes active flags
 * @width: read width
 * @precision: Precision condition
 * @size: Size condition
 * Return: Number of chars to display
 */
int display_hexa_upper(va_list types, char buff[],
	int flags, int width, int precision, int size)
{
	return (display_hexa(types, "0123456789ABCDEF", buff,
		flags, 'X', width, precision, size));
}

/**
 * display_hexa - display a hexadecimal number in lower or upper
 * @types: List of arguments
 * @map_to: array of values to map the number to
 * @buff: Buff array to help display
 * @flags: computes active flags
 * @flag_ch: computes active flags
 * @width: read width
 * @precision: Precision condition
 * @size: Size condition
 * @size: Size condition
 * Return: Number of chars to display
 */
int display_hexa(va_list types, char map_to[], char buff[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = change_size_unsgnd(num, size);

	if (num == 0)
		buff[i--] = '0';

	buff[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buff[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & HASH && init_num != 0)
	{
		buff[i--] = flag_ch;
		buff[i--] = '0';
	}
	i++;
	return (write_unsgnd(0, i, buff, flags, width, precision, size));
}
