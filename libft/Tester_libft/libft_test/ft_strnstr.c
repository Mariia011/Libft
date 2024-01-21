// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>

#include <string.h>
#include <bsd/string.h>
#include "rand/utils.h"
#include "rand/numbers.h"
#include "rand/strings.h"
#include "utils/utils.h"

#define EURO_SYMBOL ((unsigned char)128)

typedef struct s_strnstr_param
{
	char *haystack;
	char *needle;
	size_t n;
} t_strnstr_param;

char *ft_strnstr(const char *haystack, const char *needle, size_t n);
static void validate_strnstr(
	void *haystack,
	void *needle,
	size_t len,
	int free);

TestSuite(ft_strnstr, .timeout=TIMEOUT);

ParameterizedTestParameters(ft_strnstr, simple)
{
	static t_strnstr_param data[] = {
		{ .haystack = "0123456789", .needle  = "345", .n = 10 },
		{ .haystack = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", .needle  = "QRS", .n = 19 },
		{ .haystack = "0123456789", .needle  = "345", .n = 2 },
		{ .haystack = "0123456789", .needle  = "345", .n = 5 },
		{ .haystack = "0123456789", .needle  = "345", .n = 10 },
		{ .haystack = "", .needle  = "", .n = 10 },
		{ .haystack = "0123456789", .needle  = "1", .n = 0 },
		{ .haystack = "0123456789", .needle  = "", .n = 0 },
		{ .haystack = "0123456789ABCDEF", .needle  = "0123456789", .n = 10 },
	};
	return cr_make_param_array(t_strnstr_param, data,
		sizeof(data) / sizeof(*data));
}

ParameterizedTest(t_strnstr_param *param, ft_strnstr, simple)
{
	validate_strnstr(param->haystack, param->needle, param->n, false);
}

Test(ft_strnstr, extended_ascii)
{
	char h[11] = "0123456789\0";
	char n[4] = "345\0";

	h[4] = EURO_SYMBOL;
	n[1] = EURO_SYMBOL;

	validate_strnstr(h, n, strlen(h), false);
}

Test(ft_strnstr, randomised)
{
	int i, len, src, nbr;
	void *h, *n;

	for (i = 0; i < RAND_ITERATIONS; i++)
	{
		len = (int)rand_number_between(2, 500);
		rand_string(CHARSET_EXTENDED, len, &h, NULL);
		if (rand_number_max(2) == 0)
		{
			src = (int)rand_number_max(len - 1);
			nbr = (int)rand_number_between(src, len);
			n = ft_malloc(nbr + 1);
			strncpy(n, &((char *)h)[src], nbr);
			((char *)n)[nbr] = '\0';
		}
		else
		{
			rand_string(CHARSET_EXTENDED, (int)rand_number_max(500), &n, NULL);
		}

		validate_strnstr(h, n, rand_number_max(500), true);
	}
}

static void validate_strnstr(void *haystack, void *needle, size_t len, int free)
{
	void *ret0, *ret1;

	ret0 = strnstr(haystack, needle, len);
	ret1 = ft_strnstr(haystack, needle, len);

	if (free == true)
	{
		ft_free(haystack);
		ft_free(needle);
	}

	cr_assert(
		ret0 == ret1, "Wrong return value got %p expected %p.", ret1, ret0);
}
