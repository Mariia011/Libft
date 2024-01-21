// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>

#include <limits.h>
#include <stdio.h>
#include "utils/utils.h"
#include "rand/utils.h"
#include "rand/numbers.h"

int ft_atoi(const char *str);
static void validate_atoi(char *str);

TestSuite(ft_atoi, .timeout=TIMEOUT);

ParameterizedTestParameters(ft_atoi, simple)
{
	static char *data[] = { "0", "42", "-42", "2147483647", "-2147483648",
							"     666plop", "\t5\v", " 35 5" };

	return cr_make_param_array(char *, data, sizeof(data) / sizeof(*data));
}

ParameterizedTest(char **c, ft_atoi, simple)
{
	validate_atoi(*c);
}

Test(ft_atoi, randomised)
{
	int i;
	char *str;

	str = alloca(20);
	for (i = 0; i < RAND_ITERATIONS; i++)
	{
		snprintf(str, 20, "%d", (int)rand_number_between_signed(INT_MIN,
			(unsigned int)INT_MAX + 1));
		validate_atoi(str);
	}
}

void validate_atoi(char *str)
{
	int ret0, ret1;

	ret0 = atoi(str);
	ret1 = ft_atoi(str);

	cr_assert(ret0 == ret1, "Wrong return value for \"%s\" got %d expected %d.",
		str, ret1, ret0);
}
