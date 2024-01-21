// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "strings.h"
#include "../utils/utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int ft_get_charset_size(unsigned char flags);
static int ft_get_charset(unsigned char flags, char **ptr);
static void ft_string_from_charset(
	char *charset, int charset_len, int len, char **str);

static int ft_get_charset(unsigned char flags, char **ptr)
{
	int size, i;

	size = ft_get_charset_size(flags);
	*ptr = (typeof(*ptr))ft_malloc(sizeof(**ptr) * (size + 1));

	(*ptr)[size] = 0;
	size--;
	if ((flags & CHARSET_UPPERCASE) > 0)
	{
		for (i = 'A'; i <= 'Z'; i++)
			(*ptr)[size--] = i;
	}
	if ((flags & CHARSET_LOWERCASE) > 0)
	{
		for (i = 'a'; i <= 'z'; i++)
			(*ptr)[size--] = i;
	}
	if ((flags & CHARSET_NUMBERS) > 0)
	{
		for (i = '0'; i <= '9'; i++)
			(*ptr)[size--] = i;
	}
	if ((flags & CHARSET_SYMBOLS) > 0)
	{
		for (i = ' '; i <= '/'; i++)
			(*ptr)[size--] = i;
		for (i = ':'; i <= '@'; i++)
			(*ptr)[size--] = i;
		for (i = '['; i <= '`'; i++)
			(*ptr)[size--] = i;
		for (i = '{'; i <= '~'; i++)
			(*ptr)[size--] = i;
	}
	if ((flags & CHARSET_NON_PRINTABLE) > 0)
	{
		for (i = 1; i < 32; i++)
			(*ptr)[size--] = i;
		(*ptr)[size--] = 127;
	}
	if ((flags & CHARSET_NULL) > 0)
	{
		(*ptr)[size--] = 0;
	}
	if ((flags & CHARSET_EXTENDED) > 0)
	{
		for (i = 0; i < 128; i++)
			(*ptr)[size--] = i + 128;
	}
	return (size);
}

static int ft_get_charset_size(unsigned char flags)
{
	int size;

	size = 0;
	if ((flags & CHARSET_LOWERCASE) > 0)
	{
		size += 26;
	}
	if ((flags & CHARSET_UPPERCASE) > 0)
	{
		size += 26;
	}
	if ((flags & CHARSET_NUMBERS) > 0)
	{
		size += 10;
	}
	if ((flags & CHARSET_NON_PRINTABLE) > 0)
	{
		size += 32;
	}
	if ((flags & CHARSET_NULL) > 0)
	{
		size++;
	}
	if ((flags & CHARSET_SYMBOLS) > 0)
	{
		size += 33;
	}
	if ((flags & CHARSET_EXTENDED) > 0)
	{
		size += 128;
	}

	return (size);
}

static void ft_string_from_charset(
	char *charset, int charset_len, int len, char **str)
{
	int i;

	*str = (typeof(*str))ft_malloc(sizeof(**str) * (len + 1));
	for (i = 0; i < len; i++)
	{
		(*str)[i] = charset[rand() % charset_len];
	}
	(*str)[len] = 0;
}

/*
 * Creates a NULL-terminated string of length n into copy0 following rules
 * defined in flags.
 * Makes a copy of it in copy1, if copy1 is not NULL
 */
void rand_string(unsigned char flags, int n, void **copy0, void **copy1)
{
	char *charset;
	int charset_len;

	charset_len = ft_get_charset(flags, &charset);
	ft_string_from_charset(charset, charset_len, n, (char **)copy0);
	if (copy1 != NULL)
	{
		*copy1 = (typeof(copy1))ft_malloc(sizeof(*copy1) * (n + 1));
		memcpy(*copy1, *copy0, n + 1);
	}
	ft_free(charset);
}
