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

#define A_ACCENT ((unsigned char)224)

int ft_strncmp(const char *s1, const char *s2, size_t n);
static void validate_strncmp(void *s1, void *s2, size_t n, int free);
static int sign(int a);

TestSuite(ft_strncmp, .timeout=TIMEOUT);

Test(ft_strncmp, identical)
{
	char *str0 = "0123456789";
	char *str1 = "0123456789";

	validate_strncmp(str0, str1, strlen(str0) + 1, false);
}

Test(ft_strncmp, different)
{
	char *str0 = "01234S6789";
	char *str1 = "01234X6789";

	validate_strncmp(str0, str1, strlen(str0) + 1, false);
}

Test(ft_strncmp, 0)
{
	char *str0 = "";
	char *str1 = "";

	validate_strncmp(str0, str1, 0, false);
}

Test(ft_strncmp, extended_ascii)
{
	char str0[11] = "01234.6789";
	char str1[11] = "01234a6789";

	str0[5] = A_ACCENT;
	validate_strncmp(str0, str1, strlen(str0) + 1, false);
}

Test(ft_strncmp, different_size)
{
	char *str0 = "01234";
	char *str1 = "0123456789";

	validate_strncmp(str0, str1, strlen(str1) + 1, false);
}

Test(ft_strncmp, randomised)
{
	int i, n;
	void *s1, *s2;

	for (i = 0; i < RAND_ITERATIONS; i++)
	{
		n = (int)rand_number_max(500);
		rand_string(CHARSET_EXTENDED, n, &s1, &s2);
		if (rand() % 3 == 0 && n != 0)
		{
			n = (int)rand_number_max(n);
			((char *)s1)[n] = '\0';
		}
		if (rand() % 3 == 0 && n != 0)
		{
			n = (int)rand_number_max(n);
			((char *)s1)[n] = (char)rand_number_max(256);
		}
		validate_strncmp(s1, s2, n, true);
	}
}

void validate_strncmp(void *s1, void *s2, size_t n, int free)
{
	int ret0, ret1;

	ret0 = strncmp(s1, s2, n);
	ret1 = ft_strncmp(s1, s2, n);

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
