/*
 * file: handle_specifiers.c
 * Auth: Solly Matlakala
 *	 Algah Nkosi
 */

#include "main.h"

/**
 * handle_specifiers - handles various format specifiers and prints
 * values based on the format string and arguments
 * @fmt: input arguments
 * @ind: pointer to index format string
 * @args: handles arguments
 * @buffer: stores output
 * @flags: claculates active flags
 * @width: handles width
 * @precision: specify precision
 * @size: specifies the length
 * Return: number of characters printed
 */
int handle_specifiers(const char *fmt, int *ind, va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int get_length = 0;

	fmt_t fmt_types[] = {
	{'c', handle_char}, {'s', handle_string}, {'%', handle_percent},
	{'i', handle_int}, {'d', handle_int}, {'b', handle_binary},
	{'u', handle_unsigned}, {'o', handle_octal}, {'x', handle_hexadecimal},
	{'X', handle_hexa_upper}, {'p', handle_pointer}, {'S', handle_
							 non_printable},
	{'r', handle_reverse}, {'R', handle_rot13str}, {'\0', NULL}
	};

	for (int i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(args, buffer, flags, width,
					 precision, size));
	}

	if (fmt[*ind] == '\0')
		return (-1);
	if (fmt[*ind] == '%')
	{
		get_length += write(1, "%", 1);
		if (fmt[*ind - 1] == ' ')
		{
			get_length += write(1, " ", 1);
		}
		else if (width)
		{
			(*ind)--;
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				(*ind)--;

			if (fmt[*ind] == ' ')
				(*ind)--;
			return (1);
		}
	}
	else
	{
		get_length += write(1, &fmt[*ind], 1);
	}

	(*ind)++;
	return (get_length);

}