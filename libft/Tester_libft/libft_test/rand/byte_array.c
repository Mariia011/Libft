// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "byte_array.h"
#include "../utils/utils.h"
#include <string.h>
#include <stdlib.h>

static unsigned char default_generator();

static unsigned char default_generator()
{
	static short rand_max_bytes = -1;
	static short current_rand_bytes = 0;
	static int rnd;
	unsigned char ret;

	if (rand_max_bytes == -1)
	{
		rand_max_bytes = 0;
		rnd = RAND_MAX;
		while ((rnd & 255) == 255)
		{
			rnd >>= 8;
			rand_max_bytes++;
		}
	}
	if (current_rand_bytes == 0)
	{
		rnd = rand();
		current_rand_bytes = rand_max_bytes;
	}
	ret = rnd & 255;
	rnd >>= 8;
	current_rand_bytes--;

	return (ret);
}

/*
 * Creates a non NULL-terminated array of n pseudo random bytes in copy0
 * Makes a copy of it in copy1, if copy1 is not NULL
 */
void ft_byte_array(unsigned int n, void **copy0, void **copy1)
{
	return ft_byte_array_generator(n, copy0, copy1, default_generator);
}

/*
 * Creates a non NULL-terminated array of n*size pseudo random bytes in copy0
 * Makes a copy of it in copy1, if copy1 is not NULL
 */
void ft_elem_array(
	unsigned int n, unsigned int size, void **copy0, void **copy1)
{
	return ft_byte_array(n * size, copy0, copy1);
}

/*
 * Creates a non NULL-terminated array of n bytes in copy0
 * Makes a copy of it in copy1, if copy1 is not NULL
 * The bytes are obtained from calling g()
 */
void ft_byte_array_generator(
	unsigned int n, void **copy0, void **copy1, t_generator g)
{
	unsigned int size;

	size = n;
	*copy0 = (typeof(*copy0))ft_malloc(n);

	while (n > 0)
	{
		((unsigned char *)*copy0)[--n] = g();
	}
	if (copy1 != NULL)
	{
		*copy1 = (typeof(*copy1))ft_malloc(size);
		memcpy(*copy1, *copy0, size);
	}
}

/*
 * Creates a non NULL-terminated array of n*size bytes in copy0
 * Makes a copy of it in copy1, if copy1 is not NULL
 * The bytes are obtained from calling g()
 */
void ft_elem_array_generator(
	unsigned int n,
	unsigned int size,
	void **copy0,
	void **copy1,
	t_generator g)
{
	return ft_byte_array_generator(n * size, copy0, copy1, g);
}