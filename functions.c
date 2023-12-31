#include "main.h"



/************************* PRINT CHAR *************************/

/**
 * print_char - function to print a character
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @types: Lista of arguments
 * @width: get width
 * @precision: Precision specification
 * @flags:  Calculates active flags
 * Return: Characters being printed in number
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}



/********************** PRINT A STRING **********************/
/**
 * print_string - Prints a string
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @types: Lista of arguments
 * @width: get width
 * @precision: Precision specification
 * @flags:  Calculates active flags
 * Return: Characters being printed in number
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, x;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
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
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (x = width - length; x > 0; x--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (x = width - length; x > 0; x--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @types: Lista of arguments
 * @width: get width
 * @precision: Precision specification
 * @flags:  Calculates active flags
 * Return: Characters being printed in number
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}



/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @types: Lista of arguments
 * @width: get width
 * @precision: Precision specification
 * @flags:  Calculates active flags
 * Return: Characters being printed in number
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[x--] = (num % 10) + '0';
		num /= 10;
	}

	x++;

	return (write_number(is_negative, x, buffer, flags, width, precision, size));
}



/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @types: Lista of arguments
 * @width: get width
 * @precision: Precision specification
 * @flags:  Calculates active flags
 * Return: Characters being printed in number
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int w, v, x, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	w = va_arg(types, unsigned int);
	v = 2147483648; /* (2 ^ 31) */
	a[0] = w / v;
	for (x = 1; x < 32; x++)
	{
		v /= 2;
		a[x] = (w / v) % 2;
	}
	for (x = 0, sum = 0, count = 0; x < 32; x++)
	{
		sum += a[x];
		if (sum || x == 31)
		{
			char z = '0' + a[x];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
