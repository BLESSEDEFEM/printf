#include "main.h"
/************************* WRITE HANDLE *************************/
/**
* handle_write_char - Prints a string
* @c: Types for character
* @buffer: Print handling buffer array
* @flags: To calculate flags that are active
* @width: Variable for width.
* @precision: Variable that specifies precision
* @size: Variable that specifies size
*
* Return: Characters being printed in number
*/
int handle_write_char(char c, char buffer[],
int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
int a = 0;
char padd = ' ';
UNUSED(precision);
UNUSED(size);
if (flags & F_ZERO)
padd = '0';
buffer[i++] = c;
buffer[i] = '\0';
if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
for (a = 0; a < width - 1; a++)
buffer[BUFF_SIZE - a - 2] = padd;
if (flags & F_MINUS)
return (write(1, &buffer[0], 1) +
write(1, &buffer[BUFF_SIZE - a - 1], width - 1));
else
return (write(1, &buffer[BUFF_SIZE - a - 1], width - 1) +
write(1, &buffer[0], 1));
}
return (write(1, &buffer[0], 1));
}
/************************* WRITE NUMBER *************************/
/**
* write_number - Prints a string
* @is_negative: Arguments lista
* @ind: Variable for types of character
* @buffer: Buffer array to handle print
* @flags: Variable to calculate flags that are active
* @width: Variable for width.
* @precision: Variable that specifies precision
* @size: Variable that specifies size
*
* Return: Characters being printed in number
*/
int write_number(int is_negative, int ind, char buffer[],
int flags, int width, int precision, int size)
{
int length = BUFF_SIZE - ind - 1;
char padd = ' ', extra_ch = 0;
UNUSED(size);
if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (is_negative)
extra_ch = '-';
else if (flags & F_PLUS)
extra_ch = '+';
else if (flags & F_SPACE)
extra_ch = ' ';
return (write_num(ind, buffer, flags, width, precision,
length, padd, extra_ch));
}
/**
* write_num – Writing of certain a number using bufffer
* @ind: Index at which the number starts on the buffer
* @buffer: Variable to show buffer
* @flags: Variable for flags
* @width: Variable for width
* @prec: Variable to specify precision
* @length: Variable for length of number
* @padd: Variable for pading character
* @extra_c: The variable for extra character
*
* Return: Number of printed chars.
*/
int write_num(int ind, char buffer[],
int flags, int width, int prec,
int length, char padd, char extra_c)
{
int a, padd_start = 1;
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
return (0); /* printf(".0d", 0) no char is printed */
if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
if (prec > 0 && prec < length)
padd = ' ';
while (prec > length)
buffer[--ind] = '0', length++;
if (extra_c != 0)
length++;
if (width > length)
{
for (a = 1; a < width - length + 1; a++)
buffer[a] = padd;
buffer[a] = '\0';
if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
{
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length) + write(1, &buffer[1], a - 1));
}
else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
{
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[1], a - 1) + write(1, &buffer[ind], length));
}
else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
{
if (extra_c)
buffer[--padd_start] = extra_c;
return (write(1, &buffer[padd_start], a - padd_start) +
write(1, &buffer[ind], length - (1 - padd_start)));
}
}
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length));
}
/**
* write_unsgnd – Function to write a number unsigned
* @is_negative: Number indicating if the num is negative
* @ind: Index upon which number begins in buffer
* @buffer: Variable to show character arrays
* @flags: Flags specifiers
* @width: Variable to specify width
* @precision: Variable to specify precision
* @size: Variable to specify size
*
* Return: Number of written chars.
*/
int write_unsgnd(int is_negative, int ind,
char buffer[],
int flags, int width, int precision, int size)
{
/* The number is stored at the bufer's right and starts at position i */
int length = BUFF_SIZE - ind - 1, i = 0;
char padd = ' ';
UNUSED(is_negative);
UNUSED(size);
if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
return (0); /* printf(".0d", 0) no char is printed */
if (precision > 0 && precision < length)
padd = ' ';
while (precision > length)
{
buffer[--ind] = '0';
length++;
}
if ((flags & F_ZERO) && !(flags & F_MINUS))
padd = '0';
if (width > length)
{
for (a = 0; a < width - length; a++)
buffer[a] = padd;
buffer[a] = '\0';
if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
{
return (write(1, &buffer[ind], length) + write(1, &buffer[0], a));
}
else /* Asign extra char to left of padding [padd>buffer]*/
{
return (write(1, &buffer[0], a) + write(1, &buffer[ind], length));
}
}
return (write(1, &buffer[ind], length));
}
/**
* write_pointer - Write an address of memory
* @buffer: Characters array
* @ind: Index at which the number starts in the buffer
* @length: Variable for number length
* @width: Variable to specify width
* @flags: Variable to specify flags
* @padd: Padding representing character
* @extra_c: Variable for extra character representing character
* @padd_start: Index at which padding should start
*
* Return: Written characters in number
*/
int write_pointer(char buffer[], int ind, int length,
int width, int flags, char padd, char extra_c, int padd_start)
{
int a;
if (width > length)
{
for (a = 3; a < width - length + 3; a++)
buffer[a] = padd;
buffer[a] = '\0';
if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], length) + write(1, &buffer[3], a - 3));
}
else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
{
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[3], a - 3) + write(1, &buffer[ind], length));
}
else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
{
if (extra_c)
buffer[--padd_start] = extra_c;
buffer[1] = '0';
buffer[2] = 'x';
return (write(1, &buffer[padd_start], a - padd_start) +
write(1, &buffer[ind], length - (1 - padd_start) - 2));
}
}
buffer[--ind] = 'x';
buffer[--ind] = '0';
if (extra_c)
buffer[--ind] = extra_c;
return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}