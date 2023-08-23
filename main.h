#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

#define BUFF_SIZE 1024 /* use local buffer of 1024 chars */

/* DEFINE FLAGS */
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

/* DEFINE SIZES LENGTH MODIFIERS */
#define SIZE_SHORT 1
#define SIZE_LONG 2

/* DEFINE UNUSED VARIABLES OR PARAMETERS*/
#define UNUSED(x) (void)(x)

/**
 * struct fmt - struct to define format and associated function
 * @fmt: the format specifier
 * @fn: function pointer to associated handler function
 */
typedef struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
} fmt_t;

int _printf(const char *format, ...);
int handle_specifiers(const char *fmt, int *ind, va_list args, char buffer[],
int flags, int width, int precision, int size);

/* HANDLE CHARS AND STRINGS FUNCTIONS */
int handle_char(va_list types, char buffer[], int flags, int width,
	int precision, int size);
int handle_string(va_list types, char buffer[], int flags, int width,
	int precision, int size);
int handle_percent(va_list types, char buffer[], int flags, int width,
	int precision, int size);

/*FUNCTIONS TO HANDLE NUMBERS */
int handle_int(va_list types, char buffer[], int flags, int width,
	int precision, int size);
int handle_binary(va_list types, char buffer[], int flags, int width,
	int precision, int size);
int handle_uns(va_list types, char buffer[], int flags, int width,
	int precision, int size);
int handle_octal(va_list types, char buffer[], int flags, int width,
	int precision, int size);
int handle_hexadecimal(va_list types, char buffer[], int flags, int width,
	int precision, int size);
int handle_hexa_upper(va_list types, char buffer[], int flags, int width,
	int precision, int size);
int handle_hexa(va_list types, char map_to[], char buffer[], int flags,
	char flag_ch, int width, int precision, int size);
int handle_pointer(va_list types, char map_to[], char buffer[], int flags,
	char flag_ch, int width, int precision, int size);

/* FUNCTION TO HANDLE NON-CONVERSION SPECIFIERS */
int handle_flags(const char *format, int *i);
int handle_width(const char *format, int *i, va_list args);
int handle_precision(const char *format, int *i, va_list args);
int handle_size(const char *format, int *i);

/* FUNCTIONS TO HANDLE PRINTING */
int handle_characters(char c, char buffer[], int flags, int width);
int handle_num_format(int ind, char buffer[], int flags, int width,
	int precision, int length, char padding, char extra_char);
int handle_unsign(int is_negative, int ind, char buffer[], int flags,
	int width, int precision, int size);
int handle_number(int is_negative, int ind, char buffer[], int flags,
	int width, int precision, int size);
int write_pointer(char buffer[], int ind, int length, int width,
	int flags, char padding, char extra_char, int padd_start);
int handle_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int handle_rot13str(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*FUNCTIONS TO HANDLE INPUT VALIDATION */
int valid_digit(char c);
int valid_printable(char c);
int add_hexa_code(char ascii_code, char buffer[], int index);
long int num_type_conversion(unsigned long int num, int size);
long int convert_size_number(long int num, int size);
long int num_type_conversion(unsigned long int num, int size);

#endif /* MAIN_H */
