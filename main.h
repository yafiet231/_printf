#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define MINUS 1
#define PLUS 2
#define ZERO 4
#define HASH 8
#define SPACE 16
#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

#define S_LONG 2
#define S_SHORT 1

/**
 * struct ft - Struct the format
 *
 * @ft: The format.
 * @fn: The function associated.
 */
struct ft
{
	char ft;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct ft ft_t - Struct op
 *
 * @ft: The format.
 * @f_t: The function associated.
 */
typedef struct ft ft_t;

int _printf(const char *format, ...);
int _print(const char *ft, int *i,
va_list list, char buff[], int flags, int width, int precision, int size);

int print_char(va_list types, char buff[],
	int flags, int width, int precision, int size);
int display_string(va_list types, char buff[],
	int flags, int width, int precision, int size);
int display_percent(va_list types, char buff[],
	int flags, int width, int precision, int size);

int print_int(va_list types, char buff[],
	int flags, int width, int precision, int size);
int display_binary(va_list types, char buff[],
	int flags, int width, int precision, int size);
int display_unsigned(va_list types, char buff[],
	int flags, int width, int precision, int size);
int display_octal(va_list types, char buff[],
	int flags, int width, int precision, int size);
int display_hexadecimal(va_list types, char buff[],
	int flags, int width, int precision, int size);
int display_hexa_upper(va_list types, char buff[],
	int flags, int width, int precision, int size);

int display_hexa(va_list types, char map_to[],
char buff[], int flags, char flag_ch, int width, int precision, int size);

int display_non_printable(va_list types, char buff[],
	int flags, int width, int precision, int size);

int print_pointer(va_list types, char buff[],
	int flags, int width, int precision, int size);

int read_flags(const char *format, int *i);
int read_width(const char *format, int *i, va_list list);
int read_precision(const char *format, int *i, va_list list);
int read_size(const char *format, int *i);

int print_reverse(va_list types, char buff[],
	int flags, int width, int precision, int size);
void print_buff(char buff[], int *buff_index);

int print_rot13string(va_list types, char buff[],
	int flags, int width, int precision, int size);

int write_char(char c, char buff[],
	int flags, int width, int precision, int size);
int write_number(int is_positive, int index, char buff[],
	int flags, int width, int precision, int size);
int write_num(int index, char buff[], int flags, int width, int precision,
	int length, char padd, char extra_c);
int write_pointer(char buff[], int index, int length,
	int width, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int index,
char buff[],
	int flags, int width, int precision, int size);

int check_printable(char);
int display_hexa_code(char, char[], int);
int check_digit(char);

long int change_size_number(long int num, int size);
long int change_size_unsgnd(unsigned long int num, int size);

#endif
