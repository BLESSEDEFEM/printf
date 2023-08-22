#include "main.h"

/********************** PRINT UNSIGNED NUMBER **********************/
/**
 * print_unsigned - An unsigned number printing function
 * @buffer: Print handling buffer array
 * @precision: Specification for precision
 * @flags:  Variable to calculate active flags
 * @width: Variable for width
 * @types: Variable for list a of arguments
 * @size: Variable for size specifier
 * Return: Characters being printed in number
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[x--] = (num % 10) + '0';
		num /= 10;
	}

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/********** PRINT UNSIGNED NUMBER IN OCTAL  **************/
/**
 * print_octal - An unsigned number printing function in octal notation
 * @buffer: Print handling buffer array
 * @precision: Specification for precision
 * @flags:  Variable to calculate active flags
 * @width: Variable for width
 * @types: Variable for list a of arguments
 * @size: Variable for size specifier
 * Return: Characters being printed in number
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int x = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[x--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[x--] = '0';

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/*********** PRINT UNSIGNED NUMBER IN HEXADECIMAL ***********/
/**
 * print_hexadecimal - An unsigned number printing function in hexadecimal notation
 * @buffer: Print handling buffer array
 * @precision: Specification for precision
 * @flags:  Variable to calculate active flags
 * @width: Variable for width
 * @types: Variable for list a of arguments
 * @size: Variable for size specifier
 * Return: Characters being printed in number
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/********** PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL ***********/
/**
 * print_hexa_upper - An unsigned number in upper hexadecimal notation printing function
 * @buffer: Print handling buffer array
 * @precision: Specification for precision
 * @flags:  Variable to calculate active flags
 * @width: Variable for width
 * @types: Variable for list a of arguments
 * @size: Variable for size specifier
 * Return: Characters being printed in number
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/*********** PRINT HEXADECIMAL NUMBER IN LOWER OR UPPER ***********/
/**
 * print_hexa - A hexadecimal number in lower or upper printing function
 * @types: Variable for list a of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Print handling buffer array
 * @flags:  Variable to calculate active flags
 * @flag_ch: Second variable to calculate active flags
 * @width: Variable for width
 * @precision: Specification for precision
 * @size: Variable for size specifier
 * @size: Specification for size
 * Return: Characters being printed in number
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[x--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[x--] = flag_ch;
		buffer[x--] = '0';
	}

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}
