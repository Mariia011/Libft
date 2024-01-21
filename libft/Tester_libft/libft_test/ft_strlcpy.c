// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <bsd/string.h>
#include "utils/utils.h"
#include "rand/utils.h"
#include "rand/byte_array.h"
#include "rand/strings.h"
#include "rand/numbers.h"

size_t ft_strlcpy(char *dst, const char *src, size_t size);
static void validate_strlcpy(void *str, size_t n, int free);

TestSuite(ft_strlcpy, .timeout=TIMEOUT);

Test(ft_strlcpy, larger_size)
{
	char *str = "0123456789";

	validate_strlcpy(str, 20, false);
}

Test(ft_strlcpy, exact_size)
{
	char *str = "01234S6789";

	validate_strlcpy(str, strlen(str) + 1, false);
}

Test(ft_strlcpy, smaller_size)
{
	char *str = "01234";

	validate_strlcpy(str, 2, false);
}

Test(ft_strlcpy, zero)
{
	char *str = "";

	validate_strlcpy(str, 0, false);
}

Test(ft_strlcpy, randomised)
{
	int i, n;
	void *str;

	for (i = 0; i < RAND_ITERATIONS; i++)
	{
		n = (int)rand_number_max(500);
		rand_string(CHARSET_EXTENDED, n, &str, NULL);
		if (rand() % 2 == 0 && n > 0)
			n = (int)rand_number_max(n);
		else
			n += (int)rand_number_max(100);
		validate_strlcpy(str, n, true);
	}
}

void validate_strlcpy(void *str, size_t n, int free)
{
	size_t ret0, ret1;
	void *dest0, *dest1;
	int cmp;
	size_t size;

	size = strlen(str) + 1;
	ft_byte_array((size > n ? n : size), &dest0, &dest1);
	ret0 = strlcpy(dest0, str, n);
	ret1 = ft_strlcpy(dest1, str, n);
	cmp = 0;
	if (n > 0)
		cmp = memcmp(dest0, dest1, (size > n ? n : size));

	if (free == true)
		ft_free(str);
	ft_free(dest0);
	ft_free(dest1);

	cr_assert(ret0 == ret1, "Wrong return value got %d expected %d"
							".", ret1, ret0);
	cr_assert(
		cmp == 0, "Function did not operate as expected. (memcmp = %d)", cmp);
}
