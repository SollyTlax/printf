/*
 * File: handles_printing.c
 * Auth: Solly Matlakala
 *	 Algah Nkosi
 */

#include "main.h"

/**
 * handle_characters - Handle character formatting and writing
 * @c: Character to be written
 * @buffer: Array of chars to hold the formatted value
 * @flags: Flags specifier
 * @width: Width specifier
 * Return: Number of written chars.
 */
int handle_characters(char c, char buffer[], int flags, int width)
{
	int i = 0;
	char padding = ' ';

	if (flags & FLAG_ZERO)
		padding = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padding;

		if (flags & FLAG_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * handle_num_format - Handle numeric value formatting and writing
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars to hold the formatted value
 * @flags: Flags specifier
 * @width: Width specifier
 * @precision: Precision specifier
 * @length: Length of the number
 * @padding: Char representing the padding
 * @extra_char: Char representing an extra character (e.g., sign)
 * Return: Number of written chars.
 */

int handle_num_format(int ind, char buffer[],
	int flags, int width, int precision,
	int length, char padding, char extra_char)
{
	int i, padd_start = 1;

		if (precision == 0 && ind == BUFF_SIZE - 2 &&
	buffer[ind] == '0' && width == 0)
		return (0);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padding = ' ';

	while (precision > length)
		buffer[--ind] = '0', length++;

	if (extra_char != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padding;
		buffer[i] = '\0';

		if (flags & FLAG_MINUS && padding == ' ')
		{
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & FLAG_MINUS) && padding == ' ')
		{
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & FLAG_MINUS) && padding == '0')
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
}

int handle_numbers(int is_negative, int ind, char buffer[],
	int flags, int width, int precision)
{
	int length = BUFF_SIZE - ind - 1;
	char padding = ' ', extra_char = 0;

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		padding = '0';

	if (is_negative)
		extra_char = '-';
	else if (flags & FLAG_PLUS)
		extra_char = '+';
	else if (flags & FLAG_SPACE)
		extra_char = ' ';
	return (handle_num_format(ind, buffer, flags, width, precision,
		length, padding, extra_char));
}

/**
* handle_unsigned - format and write unsigned positive numeric values
* @ind: current index in the buffer
* @buffer: buffer itself
* @flags: formatting flags
* @precision: precision specifier
* @width: formats width
* Return: number of characters written
*/
int handle_unsigned(int ind, char buffer[],
	int flags, int width, int precision)
{
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padding = ' ';

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		padding = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padding;
		buffer[i] = '\0';

		if (flags & FLAG_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
* handle_pointer - handles the formatting and writing of memory address pointer
* @buffer: buffer itself characters
* @ind: current undex where the buffer starts
* @length: the length of the number
* @width: width specifier
* @flags: flags specifier
* @padding: padding character
* @extra_char: represent extra character
* @padd_start: index of padding start
* Return: number of written characters
*/
int handle_pointer(char buffer[], int ind, int length,
	int width, int flags, char padding, char extra_char, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padding;
		buffer[i] = '\0';

		if (flags & FLAG_MINUS && padding == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & FLAG_MINUS) && padding == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & FLAG_MINUS) && padding == '0')
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}

	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_char)
		buffer[--ind] = extra_char;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

