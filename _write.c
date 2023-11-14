#include "main.h"

/**
 * write_char - prints a string
 * @c: char types.
 * @buff: buff array to  print
 * @flags:  compute active flags.
 * @width: read width.
 * @precision: precision condition
 * @size: Size condition
 * Return: number of chars to print.
 */
int write_char(char c, char buff[],
		int flags, int width, int precision, int size)
{
	int k = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & ZERO)
		padd = '0';

	buff[k++] = c;
	buff[k] = '\0';

	if (width > 1)
	{
		buff[BUFF_SIZE - 1] = '\0';
		for (k = 0; k < width - 1; k++)
			buff[BUFF_SIZE - k - 2] = padd;

		if (flags & MINUS)
			return (write(1, &buff[0], 1) +
					write(1, &buff[BUFF_SIZE - k - 1], width - 1));
		else
			return (write(1, &buff[BUFF_SIZE - k - 1], width - 1) +
					write(1, &buff[0], 1));
	}

	return (write(1, &buff[0], 1));
}

/**
 * write_number - display a string
 * @is_negative: lista of arguments
 * @index: char types.
 * @buff: Buff array to print
 * @flags: computes active flags
 * @width: read width.
 * @precision: precision condition
 * @size: Size condition
 * Return: number of chars printed.
 */
int write_number(int is_negative, int index, char buff[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & ZERO) && !(flags & MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & PLUS)
		extra_ch = '+';
	else if (flags & SPACE)
		extra_ch = ' ';

	return (write_num(index, buff, flags, width, precision,
				length, padd, extra_ch));
}

/**
 * write_num - write a number using bufffer
 * @index: at which the number starts on the buffer
 * @buff: buff
 * @flags: flags
 * @width: width
 * @prec: precision condition
 * @length: number length
 * @padd: pading char
 * @extra_c: extra char
 * Return: number of printed chars.
 */
int write_num(int index, char buff[],
		int flags, int width, int prec,
		int length, char padd, char extra_c)
{
	int k, padd_start = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && buff[index] == '0' && width == 0)
		return (0);
	if (prec == 0 && index == BUFF_SIZE - 2 && buff[index] == '0')
		buff[index] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buff[--index] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (k = 1; k < width - length + 1; k++)
			buff[k] = padd;
		buff[k] = '\0';
		if (flags & MINUS && padd == ' ')
		{
			if (extra_c)
				buff[--index] = extra_c;
			return (write(1, &buff[index], length) + write(1, &buff[1], k - 1));
		}
		else if (!(flags & MINUS) && padd == ' ')
		{
			if (extra_c)
				buff[--index] = extra_c;
			return (write(1, &buff[1], k - 1) + write(1, &buff[index], length));
		}
		else if (!(flags & MINUS) && padd == '0')
		{
			if (extra_c)
				buff[--padd_start] = extra_c;
			return (write(1, &buff[padd_start], k - padd_start) +
					write(1, &buff[index], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buff[--index] = extra_c;
	return (write(1, &buff[index], length));
}

/**
 * write_unsgnd - writes an unsigned number
 * @is_negative: number shows if the number is negative
 * @index: at which the number starts in the buffer
 * @buff: array of chars
 * @flags: flags specifiers
 * @width: width specifier
 * @precision: Precision condition
 * @size: Size condition
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int index,
		char buff[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1, k = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buff[index] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buff[--index] = '0';
		length++;
	}

	if ((flags & ZERO) && !(flags & MINUS))
		padd = '0';

	if (width > length)
	{
		for (k = 0; k < width - length; k++)
			buff[k] = padd;

		buff[k] = '\0';

		if (flags & MINUS)
		{
			return (write(1, &buff[index], length) + write(1, &buff[0], k));
		}
		else
		{
			return (write(1, &buff[0], k) + write(1, &buff[index], length));
		}
	}
	return (write(1, &buff[index], length));
}
/**
 * write_pointer - write a memory address
 * @buff: arrays of the chars
 * @index: at which the number starts
 * @length: length of number
 * @width: width condtion
 * @flags: flags condition
 * @padd: char representing
 * @extra_c: char representing on extra char
 * @padd_start: index at which padding start
 * Return: Number of written chars.
 */
int write_pointer(char buff[], int index, int length,
		int width, int flags, char padd, char extra_c, int padd_start)
{
	int k;

	if (width > length)
	{
		for (k = 3; k < width - length + 3; k++)
			buff[k] = padd;
		buff[k] = '\0';
		if (flags & MINUS && padd == ' ')
		{
			buff[--index] = 'x';
			buff[--index] = '0';
			if (extra_c)
				buff[--index] = extra_c;
			return (write(1, &buff[index], length) + write(1, &buff[3], k - 3));
		}
		else if (!(flags & MINUS) && padd == ' ')
		{
			buff[--index] = 'x';
			buff[--index] = '0';
			if (extra_c)
				buff[--index] = extra_c;
			return (write(1, &buff[3], k - 3) + write(1, &buff[index], length));
		}
		else if (!(flags & MINUS) && padd == '0')
		{
			if (extra_c)
				buff[--padd_start] = extra_c;
			buff[1] = '0';
			buff[2] = 'x';
			return (write(1, &buff[padd_start], k - padd_start) +
					write(1, &buff[index], length - (1 - padd_start) - 2));
		}
	}
	buff[--index] = 'x';
	buff[--index] = '0';
	if (extra_c)
		buff[--index] = extra_c;
	return (write(1, &buff[index], BUFF_SIZE - index - 1));
}
