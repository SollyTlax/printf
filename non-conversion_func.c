/*
 * File: non-conversion_func.c
 * Auth: Solly Matlakala
 *	 Algah Nkosi
 */
#include "main.h"

/**
 * handle_size -  extracting size modifiers from a format string
 * used in a formatted output
 * @format: a pointer to a format string
 * @i: a pointer to an integer index in format string
 *
 * Return: size
 */
int handle_size(const char *format, int *i)
{
	int curr_index = *i + 1;
	int size = 0;

	if (format[curr_index] == 'l')
		size = SIZE_LONG;
	else if (format[curr_index] == 'h')
		size = SIZE_SHORT;

	if (size == 0)
		*i = curr_index - 1;
	else
		*i = curr_index;

	return (size);
}
/**
 * handle_width - extracts the width field from a format string
 * in the context of a formatted output of a function
 * @format: a pointer to a format string
 * @i: a pointer to an integer representing current position in the string
 * @args: variable for handling arguments
 *
 * Return: extracted width
 */

int handle_width(const char *format, int *i, va_list args)
{
	int curr_index;
	int width = 0;

	for (curr_index = *i + 1; format[curr_index] != '\0'; curr_index++)
	{
		if (valid_digit(format[curr_index]))
		{
			width *= 10;
			width += format[curr_index] - '0';
		}
		else if (format[curr_index] == '*')
		{
			curr_index++;
			width = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*i = curr_index - 1;

	return (width);
}

/**
 * handle_precision -  extracts the precision value from a format string
 * in the context of a formatted output in a function
 * @format: : a pointer to a format string
 * @i: a pointer to an integer represent the current position in the string
 * @args:  for variable argument handling
 *
 * Return: extracted precision
 */
int handle_precision(const char *format, int *i, va_list args)
{
	int curr_index = *i + 1;
	int precision = -1;

	if (format[curr_index] != '.')
		return (precision);

	precision = 0;

	for (curr_index += 1; format[curr_index] != '\0'; curr_index++)
	{
		if (valid_digit(format[curr_index]))
		{
			precision *= 10;
			precision += format[curr_index] - '0';
		}
		else if (format[curr_index] == '*')
		{
			curr_index++;
			precision = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*i = curr_index - 1;

	return (precision);
}

/**
 * handle_flags - extract and process formatting flags from a string used in
 * output function
 * @format: a pointer to a format string
 * @i: current position in the format string
 *
 * Return: Flags
 */
int handle_flags(const char *format, int *i)
{

	int j, curr_index;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {FLAG_MINUS, FLAG_PLUS, FLAG_ZERO,
		 FLAG_HASH, FLAG_SPACE, 0};

	for (curr_index = *i + 1; format[curr_index] != '\0'; curr_index++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[curr_index] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = curr_index - 1;

	return (flags);
}
