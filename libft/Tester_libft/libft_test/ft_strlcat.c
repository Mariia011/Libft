// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#ifdef __linux__
	#include <bsd/string.h> // for strlcat
#endif
#include "utils/utils.h"
#include "rand/numbers.h"
#include "rand/strings.h"
#include "rand/utils.h"

size_t ft_strlcat(char *dest, const char *src, size_t n);
static void validate_strlcat(
	void *src, void *dest0, void *dest1, size_t size, size_t len, int free);

TestSuite(ft_strlcat, .timeout=TIMEOUT);

Test(ft_strlcat, string)
{
	char *src = "This is a test string";
	char dest0[50] = "This is another\0";
	char dest1[50] = "This is another\0";
	validate_strlcat(src, dest0, dest1, 49, 49, false);
}

Test(ft_strlcat, part)
{
	char *src = "This is a test string";
	char dest0[50] = "This is another\0";
	char dest1[50] = "This is another\0";
	validate_strlcat(src, dest0, dest1, 25, 49, false);
}

Test(ft_strlcat, reduce)
{
	char *src = "This is a test string";
	char dest0[50] = "This is another\0";
	char dest1[50] = "This is another\0";
	validate_strlcat(src, dest0, dest1, 10, 49, false);
}

Test(ft_strlcat, empty)
{
	char *src = "";
	char dest0[1] = "\0";
	char dest1[1] = "\0";
	validate_strlcat(src, dest0, dest1, 0, 0, false);
}

Test(ft_strlcat, no_space_left)
{
	char *src = "This is a test string";
	char  dest0[1] = "\0";
	char  dest1[1] = "\0";
	validate_strlcat(src, dest0, dest1, 0, 0, false);
}

Test(ft_strlcat, randomised)
{
	void *src;
	void *dest0, *dest1;
	int i, n, n0, n1;

	for (i = 0; i < RAND_ITERATIONS; i++)
	{
		n0 = (int)rand_number_max(500);
		n1 = (int)rand_number_max(500);
		n = (int)rand_number_max(n0 + n1);
		rand_string(CHARSET_EXTENDED, n0, &src, NULL);
		rand_string(CHARSET_EXTENDED, n0 + n1, &dest0, &dest1);
		((char *)dest0)[n1] = '\0';
		((char *)dest1)[n1] = '\0';

		validate_strlcat(src, dest0, dest1, n, n0+n1, true);
	}
}

static void validate_strlcat(
	void *src, void *dest0, void *dest1, size_t size, size_t len, int free)
{
	size_t res0, res1;
	int cmp;

	res0 = strlcat(dest0, src, size);
	res1 = ft_strlcat(dest1, src, size);
	cmp = memcmp(dest0, dest1, len+1);

	if (free == true)
	{
		ft_free(src);
		ft_free(dest0);
		ft_free(dest1);
	}

	cr_assert(
		res1 == res0, "Wrong return value got %p expected %p", res1, res0);
	cr_assert(
		cmp == 0, "Function did not operate as expected. (memcmp = %d)", cmp);
}
