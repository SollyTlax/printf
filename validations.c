/*
* File: validations.c
* Auth: Solly Matlakala
*	Algah Nkosi
*/

#include "main.h"

/**
 * valid_digit - Checks if a character is a digit (0-9).
 * @c: The character to be checked.
 *
 * Return: 1 if is a valid digit
 * 0 otherwise.
 */
int valid_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * valid_printable - Checks if a character is a printable ASCII character.
 * @c: The character to be checked.
 *
 * Return: 1 if is a valid printable character
 * 0 otherwise.
 */
int valid_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * add_hexa_code - Appends a hexadecimal code to a buffer.
 * @ascii_code: The ASCII code to be converted to hexadecimal.
 * @buffer: The buffer to which the hexadecimal code will be appended.
 * @index: The current index in the buffer.
 *
 * Return: The updated index after appending the hexadecimal code.
 */
int add_hexa_code(char ascii_code, char buffer[], int index)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[index++] = '\\';
	buffer[index++] = 'x';

	buffer[index++] = map_to[ascii_code / 16];
	buffer[index] = map_to[ascii_code % 16];

	return (index + 1);
}

/**
 * num_type_conversion - Convert a number to the specified size.
 * @num: The number to be converted.
 * @size: The desired size (SIZE_LONG, SIZE_SHORT, or default).
 *
 * Return: The converted number.
 */
long int num_type_conversion(unsigned long int num, int size)
{
	if (size == SIZE_LONG)
		return (num);
	else if (size == SIZE_SHORT)
		return ((unsigned short) num);

	return ((unsigned int) num);
}

/**
 * convert_size_number - Convert a number to the specified size.
 * @num: The number to be converted.
 * @size: The desired size (SIZE_LONG, SIZE_SHORT, or default).
 *
 * Return: The converted number.
 */
long int convert_size_number(long int num, int size)
{
	if (size == SIZE_LONG)
		return (num);
	else if (size == SIZE_SHORT)
		return ((short) num);

	return ((int) num);
}

