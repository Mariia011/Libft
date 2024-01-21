// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <string.h>
#include <ctype.h>
#include "utils/utils.h"

int ft_toupper(int c);

TestSuite(ft_toupper, .timeout=TIMEOUT);

Test(ft_toupper, all_characters)
{
	int c;
	int ret0, ret1;

	for (c = 0; c < 256; c++)
	{
		ret0 = toupper(c);
		ret1 = ft_toupper(c);

		cr_assert(ret0 == ret1, "Wrong return value"
														  " for character %d got %d"
														  " expected %d.", c, ret1, ret0);
	}
}
