// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <string.h>
#include "rand/strings.h"
#include "rand/utils.h"
#include "utils/utils.h"
#include "rand/byte_array.h"
#include "rand/numbers.h"
#include <stdlib.h>

void *ft_memcpy(void *dest, const void *src, size_t n);
static void validate_memcpy(void *src, size_t n, int free);

TestSuite(ft_memcpy, .timeout=TIMEOUT);

Test(ft_memcpy, normal)
{
	char src[10] = "01234567@@";

	validate_memcpy(src, 10, false);
}

Test(ft_memcpy, 0)
{
	char src[10] = "aabbccddee";

	validate_memcpy(src, 0, false);
}

Test(ft_memcpy, randomised)
{
	int i, n;
	void *src;

	for (i = 0; i < RAND_ITERATIONS; i++)
	{
		n = rand_number_max(500);
		ft_byte_array(n, &src, NULL);

		validate_memcpy(src, n, true);
	}
}

static void validate_memcpy(void *src, size_t n, int free)
{
	void *dest0, *dest1;
	void *ret;
	int cmp;

	ft_byte_array(n, &dest0, &dest1);
	memcpy(dest0, src, n);
	ret = ft_memcpy(dest1, src, n);
	cmp = memcmp(dest0, dest1, n);

	if (free == true)
		ft_free(src);
	ft_free(dest0);
	ft_free(dest1);

	cr_assert(
		ret == dest1, "Wrong return value got %p expected %p.", ret, dest1);
	cr_assert(
		cmp == 0, "Function did not operate as expected. (memcmp = %d)", cmp);
}

