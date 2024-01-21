// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <string.h>
#include "utils/utils.h"
#include "rand/utils.h"
#include "rand/numbers.h"
#include "rand/strings.h"
static void validate_strlen(void *ptr0, int free);
size_t ft_strlen(const char *s);

TestSuite(ft_strlen, .timeout=TIMEOUT);

Test(ft_strlen, normal)
{
	char *str = "abcdefghi";
	validate_strlen(str, false);
}

Test(ft_strlen, 0)
{
	char *str = "\0abcd";
	validate_strlen(str, false);
}

Test(ft_strlen, randomised)
{
	void *ptr0;
	int i, n;

	for (i = 0; i < RAND_ITERATIONS; i++)
	{
		n = rand_number_max(500);
		rand_string(CHARSET_EXTENDED, n, &ptr0, NULL);
		validate_strlen(ptr0, true);
	}
}

static void validate_strlen(void *ptr0, int free)
{
	size_t ret0, ret1;

	ret0 = strlen(ptr0);
	ret1 = ft_strlen(ptr0);

	if (free == true)
		ft_free(ptr0);

	cr_assert(
		ret0 == ret1, "Wrong return value got %d expected %d.", ret1, ret0);
}
