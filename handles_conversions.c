/*
 * File: handles_conversions.c
 * Auth: Solly Matlakala
 *	 Algah Nkosi
 */

#include "main.h"

/**
 * handle_binary - Handles printing of binary and unsigned integers
 * @types: The va_list containing the argument
 * @buffer: Unused char buffer parameter
 * @flags: Unused flags parameter
 * @width: Unused width parameter
 * @precision: Unused precision parameter
 * @size: Unused size parameter
 *
 * Return: Number of characters written
 */
int handle_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	(void)buffer;
	(void)flags;
	(void)width;
	(void)precision;
	(void)size;

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;

	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}

	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}

	return (count);
}

/**
 * handle_char - Handle character formatting.
 * @types: A va_list of arguments.
 * @buffer: The buffer to store the formatted output.
 * @flags: Formatting flags.
 * @width: Field width.
 * @precision: Precision for formatting.
 * @size: Size of the buffer.
 *
 * Return: The number of characters written to the buffer.
 */
int handle_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_characters(c, buffer, flags, width, precision, size));
}

/**
 * handle_string - Handle string formatting.
 * @types: A va_list of arguments.
 * @buffer: The buffer (not used in this function).
 * @flags: Formatting flags (not used in this function).
 * @width: Field width.
 * @precision: Precision for formatting.
 * @size: Size of the buffer (not used in this function).
 *
 * Return: The number of characters written to the standard output.
 */

int handle_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);
	(void) size;
	(void) buffer;

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
		if (flags & FLAG_MINUS)
	{
		write(1, str, length);
	for (i = width - length; i > 0; i--)
		write(1, " ", 1);
	return (width);
	}
	else
	{
	for (i = width - length; i > 0; i--)
	write(1, " ", 1);
	write(1, str, length);
	return (width);
	}
	}

	return (write(1, str, length));
}

/**
 * handle_percent - Prints a percent symbol
 * @types: The va_list containing the argument
 * @buffer: The buffer to store the formatted string
 * @flags: Formatting flags
 * @width: Minimum field width
 * @precision: Precision for printing
 * @size: The size modifier for the number
 * Return: The number of characters written
 */
int handle_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	(void) types;
	(void) buffer;
	(void) flags;
	(void) width;
	(void) precision;
	(void) size;

	return (write(1, "%%", 1));
}


/**
 * handle_int - Handles printing of integer values
 * @types: The va_list containing the argument
 * @buffer: The buffer to store the formatted string
 * @flags: Formatting flags
 * @width: Minimum field width
 * @precision: Precision for printing
 * @size: The size modifier for the number
 *
 * Return: Number of characters written
 */
int handle_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (handle_number(is_negative, i, buffer, flags, width, precision,
		size));
}
