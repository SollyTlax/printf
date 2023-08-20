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

/**
 * struct fmt - Struct op
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef structure fmt fmt_t - struct op
 * @fmt: the format
 * @fm_t: function associated with
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_specifiers(const char *fmt, int *i, va_list args, char buffer[],
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
int handle_unsigned(va_list types, char buffer[], int flags, int width,
	 int precision, int size);
int handle_octal(va_list types, char buffer[], int flags, int width,
	 int precision, int size);
int handle_hexadecimal(va_list types, char buffer[], int flags, int width,
	 int precision, int size);
int handle_hexa_upper(va_list types, char buffer[], int flags, int width,
	 int precision, int size);
int handle_hexa(va_list types, char map_to[], char buffer[], int flags,
	 char flag_ch, int width, int precision, int size);

/* FUNCTION TO HANDLE NON-CONVERSION SPECIFIERS */
int handle_flags(const char *format, int *i);
int handle_width(const char *format, int *i, va_list args);
int handle_precision(const char *format, int *i, va_list args);
int handle_size(const char *format, int *i);

