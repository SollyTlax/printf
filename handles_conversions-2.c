/*
* File: handles_conversion-2
* Auth: Solly Matlakala
* Algah Nkosi
*/

#include "main.h"

/**
 * handle_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of charactersprinted
 */
	int  handle_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	(void)flags;
	(void)width;
	(void)precision;
	(void)size;

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += add_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * handle_pointer - Prints the value of a pointer variable
 * @types: Lists  of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int handle_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_char = 0, padding = ' ';
	int index = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	(void)width;
	(void)size;
    (void)precision;

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[index--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		padding = '0';
	if (flags & FLAG_PLUS)
		extra_char = '+', length++;
	else if (flags & FLAG_SPACE)
		extra_char = ' ', length++;

	index++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (handle_pointer(buffer, index, length,
		width, flags, padding, extra_char, padd_start));
}

/**
 * handle_reverse - Prints reverse string.
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Numbers of characters printed
 */

int handle_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int index, count = 0;

	(void)buffer;
	(void)flags;
	(void)width;
	(void)size;

	str = va_arg(types, char *);

	if (str == NULL)
	{
		(void)precision;

		str = ")Null(";
	}
	for (index = 0; str[index]; index++)
		;

	for (index = index - 1; index >= 0; index--)
	{
		char z = str[index];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/**
 * handle_rot13str - Print a string in rot13.
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Numbers of characters printed
 */
int handle_rot13str(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
