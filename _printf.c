/*
 * File: _printf.c
 * Auth: Solly Matlakala
 *       Algah Nkosi
 */
#include "main.h"

void handle_buffer(char buffer[], int *buffer_index);

/**
 * _printf - write a program that produces output according to format
 * write output to stdout, the standard output stream
 * @format: is a charactor string
 *
 * Return:the number of characters printed
 */
int _printf(const char *format, ...)
{
	int i, print, printed_chars = 0;
	int flags, width, precision, size, buffer_index = 0;
	char buffer[BUFF_SIZE];
	va_list args;

	va_start(args, format);

	if (format == NULL)
		return (-1);

	for (1 = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
		buffer[buffer_index++] = format[i];
		if (buffer_index == BUFF_SIZE)
			handle_buffer(buffer, &buffer_index);
		printed_chars++;
		}
	else
	{
		handle_buffer(buffer, &buff_index);
		flags = handle_flags(format, &i);
		width = handle_width(format, &i, args);
		precision = handle_precision(format, &i, args);
		size = handle_size(format, &i);
		++i;
		print = handle_specifiers(format, &i, args, buffer,
		flags, width, precision, size);
		if (print == -1)
			return (-1);
		printed_chars += print;
	}
	}
	handle_buffer(buffer, &buffer_index);
	va_end(args);
	return (printed_chars);
}
/**
 * handle_buffer - print the contents of a character buffer and then
 * resets the buffer index
 * @buffer: array of charactors
 * @buffer_index: a pointer to an integer in buffer index
 */
void handle_buffer(char buffer[], int *buffer_index)
{
	if (buffer_index > 0)
		write(1, &buffer[0], *buffer_index);
	*buffer_index = 0;
}
