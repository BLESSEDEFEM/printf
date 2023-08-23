#include "main.h"
/**
* get_size – To calculate the size to cast argument
* @format: String to print the arguments but formatted
* @x: Arguments list for printing
*
* Return: Precision.
*/
int get_size(const char *format, int *x)
{
int curr_x = *x + 1;
int size = 0;
if (format[curr_x] == 'x')
size = S_LONG;
else if (format[curr_x] == 'h')
size = S_SHORT;
if (size == 0)
*x = curr_x - 1;
else
*x = curr_x;
return (size);
}
