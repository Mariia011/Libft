// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <string.h>
#include "rand/utils.h"
#include "rand/numbers.h"
#include "rand/strings.h"
#include "utils/utils.h"

#define EURO_SYMBOL ((unsigned char)128)

void *ft_strrchr(const void *s, int c);
static void validate_strrchr(void *src, int c, int free);

TestSuite(ft_strrchr, .timeout=TIMEOUT);

Test(ft_strrchr, found)
{
	char buf[10] = "012345678\0";

	validate_strrchr(buf, '5', false);
}

Test(ft_strrchr, first)
{
	char buf[10] = "012345678\0";

	validate_strrchr(buf, '0', false);
}

Test(ft_strrchr, not_found)
{
	unsigned char buf[10] = "012345678\0";

	validate_strrchr(buf, '@', false);
}

Test(ft_strrchr, multiple_occurence)
{
	unsigned char buf[10] = "0@2@4@6@8\0";

	validate_strrchr(buf, '@', false);
}

Test(ft_strrchr, null)
{
	unsigned char buf[10] = "012345678\0";

	validate_strrchr(buf, '\0', false);
}

Test(ft_strrchr, extended_ascii)
{
	char buf[10] = "012345678\0";

	buf[4] = EURO_SYMBOL;
	validate_strrchr(buf, EURO_SYMBOL, false);
}

Test(ft_strrchr, randomised)
{
	int i, n, c;
	void *str;

	for (i = 0; i < RAND_ITERATIONS; i++)
	{
		n = (int)rand_number_max(500);
		rand_string(CHARSET_EXTENDED, n, &str, NULL);
		c = (int)rand_number_max(255);

		validate_strrchr(str, c, true);
	}
}

static void validate_strrchr(void *src, int c, int free)
{
	void *ret0, *ret1;

	ret0 = strrchr(src, c);
	ret1 = ft_strrchr(src, c);

	if (free == true)
		ft_free(src);

	cr_assert(
		ret0 == ret1, "Wrong return value got %p expected %p.", ret1, ret0);
}
