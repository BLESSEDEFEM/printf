#ifndef MAIN_H
#define MAIN_H
#define BUFF_SIZE 1024
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#define BUFF_SIZE 1024
#define UNUSED(x) (void)(x)

/* SIZES */
#define S_SHORT 1
#define S_LONG 2

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/**
 * struct fmt - struct op
 *
 * @fmt: format of header file
 *
 * @fn: function in conjunction with the header file
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: format of the function
 *
 * @fm_t: function in conjunction with it
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);

/**************** FUNCTIONS ****************/

/* chars and strings printing functions */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size);


/* non printable characters printing function */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* numbers printing functions */
int print_int(va_list types, char buffer[],
        int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[],
        int flags, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[],
        int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[],
        int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[],
        int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[],
        int flags, int width, int precision, int size);

int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* memory address printing function */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* other specif1iers handling functions */
int get_flags(const char *format, int *x);
int get_width(const char *format, int *x, va_list list);
int get_precision(const char *format, int *x, va_list list);
int get_size(const char *format, int *x);

/* string in reverse printing function */
int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* width handler functions */
int handle_write_char(char c, char buffer[],
        int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[],
        int flags, int width, int precision, int size);
int write_num(int ind, char bff[], int flags, int width, int precision,
        int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length,
        int width, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind,
char buffer[],
        int flags, int width, int precision, int size);

/* a string in rot 13 printing function */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size);


/**************** UTILS ****************/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */
