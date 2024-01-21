// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "numbers.h"
#include <stdlib.h>
#include "byte_array.h"

static unsigned long long rand_n_bytes(unsigned short n);
static unsigned long long rand_8_bytes();

/*
 * 0 <= n <= 8
 */
static unsigned long long rand_n_bytes(unsigned short n)
{
	unsigned long long i;
	static short rand_max_bytes = -1;
	static short current_rand_bytes = 0;
	short previous_rand_bytes;
	static int rnd;

	if (n <= 0)
		return (0);
	i = 0;
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
	i = rnd;
	rnd = 0;
	previous_rand_bytes = (n > current_rand_bytes ? current_rand_bytes : n);
	current_rand_bytes = 0;

	return ((i << (n - previous_rand_bytes))
			^ rand_n_bytes(n - previous_rand_bytes));
}

static unsigned long long rand_8_bytes()
{
	return (rand_n_bytes(8));
}

/*
 * returns a random unsigned long long with 64bits of randomness
 */
unsigned long long rand_number()
{
	return rand_8_bytes();
}

/*
 * returns a random unsigned long long in range [0,max)
 */
unsigned long long rand_number_max(unsigned long long max)
{
	return rand_8_bytes() % max;
}

/*
 * returns a random unsigned long long in range [min,max)
 */
unsigned long long rand_number_between(
	unsigned long long min,
	unsigned long long max)
{
	return (rand_8_bytes() % (max - min)) + min;
}

/*
 * returns a random long long with 64bits of randomness
 */
long long rand_number_signed()
{
	return (long long)rand_8_bytes();
}

/*
 * returns a random long long in range [min, max)
 */
long long rand_number_between_signed(long long min, long long max)
{
	return (rand_number_signed() % (max - min)) + min;
}
