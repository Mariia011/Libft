// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <string.h>
#include "utils/utils.h"
#include "rand/utils.h"
#include "rand/numbers.h"
#include "rand/byte_array.h"

#define A_ACCENT ((unsigned char)224)

int ft_memcmp(const void *s1, const void *s2, size_t n);
static void validate_memcmp(void *s1, void *s2, size_t n, int free);
static int sign(int a);

TestSuite(ft_memcmp, .timeout=TIMEOUT);

Test(ft_memcmp, identical)
{
	char buf0[10] = "0123456789";
	char buf1[10] = "0123456789";

	validate_memcmp(buf0, buf1, 10, false);
}

Test(ft_memcmp, different)
{
	char buf0[10] = "01234S6789";
	char buf1[10] = "01234X6789";

	validate_memcmp(buf0, buf1, 10, false);
}

Test(ft_memcmp, extended_ascii)
{
	unsigned char buf0[10] = "01234.6789";
	unsigned char buf1[10] = "01234a6789";

	buf0[5] = A_ACCENT;
	validate_memcmp(buf0, buf1, 10, false);
}

Test(ft_memcmp, randomised)
{
	int i, n;
	void *s1, *s2;

	for (i = 0; i < RAND_ITERATIONS; i++)
	{
		n = (int)rand_number_max(500);
		ft_byte_array(n, &s1, &s2);
		if (n > 0 && rand() % 2 == 0)
		{
			((unsigned char *)s1)[(int)rand_number_max(
				n)] = rand_number_max(256);
		}
		validate_memcmp(s1, s2, n, true);
	}
}

void validate_memcmp(void *s1, void *s2, size_t n, int free)
{
	int ret0, ret1;

	ret0 = memcmp(s1, s2, n);
	ret1 = ft_memcmp(s1, s2, n);

	if (free == true)
	{
		ft_free(s1);
		ft_free(s2);
	}

	cr_assert(sign(ret0) == sign(ret1), "Wrong return value got %d expected %d"
										".", ret1, ret0);
}

static int sign(int a)
{
	if (a == 0)
		return a;
	if (a < 0)
		return -1;
	return 1;
}
