// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <string.h>
#include "utils/utils.h"
#include "rand/byte_array.h"
#include "rand/numbers.h"
#include "rand/utils.h"

static void validate_bzero(
	void *ptr0, void *ptr1, size_t n, int free);
void ft_bzero(void *s, size_t n);

TestSuite(ft_bzero, .timeout=TIMEOUT);

Test(ft_bzero, normal)
{
	char buf0[10], buf1[10];

	validate_bzero(buf0, buf1, 10, false);
}

Test(ft_bzero, 0)
{
	char buf0[10] = ".@@@@@@@@@";
	char buf1[10] = ".@@@@@@@@@";

	validate_bzero(buf0, buf1, 0, false);
}

Test(ft_bzero, randomised)
{
	void *ptr0, *ptr1;
	int i, n;

	for (i = 0; i < RAND_ITERATIONS; i++)
	{
		n = (int)rand_number_max(500);
		ft_byte_array(n, &ptr0, &ptr1);

		validate_bzero(ptr0, ptr1, n, true);
	}
}

/*
 * Takes as input two identical memory spaces of size >= n as ptr0 and ptr1
 * Interrupts the test if ft_bzero and bzero do not behave the same
 * Compares the arrays for up to len characters
 * Frees the two memory spaces if free = 1
 */
static void validate_bzero(
	void *ptr0, void *ptr1, size_t n, int free)
{
	int cmp;

	bzero(ptr0, n);
	ft_bzero(ptr1, n);
	cmp = memcmp(ptr0, ptr1, n);

	if (free == true)
	{
		ft_free(ptr0);
		ft_free(ptr1);
	}

	cr_assert(
		cmp == 0, "Function did not operate as expected. (memcmp = %d)", cmp);
}
