// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <mimick.h>

#include <stdlib.h>
#include "utils/utils.h"
#include "rand/numbers.h"
#include "rand/strings.h"
#include "rand/utils.h"
#include "rand/byte_array.h"

#define __USE_GNU
#include <dlfcn.h>

void *ft_calloc(size_t nmemb, size_t size);
static void validate_calloc(size_t nmemb, size_t size);

TestSuite(ft_calloc, .timeout=TIMEOUT);

Test(ft_calloc, simple)
{
	validate_calloc(5, 5);
}

Test(ft_calloc, 0)
{
	validate_calloc(100, 0);
}

Test(ft_calloc, randomised)
{
	int i, a, b;

	for (i = 0; i < RAND_ITERATIONS; i++)
	{
		a = (int)rand_number_max(100);
		b = (int)rand_number_max(100);

		validate_calloc(a, b);
	}
}

mmk_mock_define (malloc_mock_fail, void *, size_t);

Test(ft_calloc, malloc_fail)
{
	void *res;
	int mimick_res;

	mmk_mock("malloc@self", malloc_mock_fail);
	mmk_when(malloc(mmk_any(size_t)), .then_return = NULL, .then_errno = ENOMEM);
	res = ft_calloc(10, 10);
	mimick_res = mmk_verify(malloc(mmk_eq(size_t, 100)), .times = 1);
	mmk_reset(malloc);

	if (mimick_res == 0)
		cr_log_warn("(%s:%s) Unexpected malloc usage (either calling it too "
					"many, or too few times, or allocating too much or not "
					"enough memory", criterion_current_suite
			->name, criterion_current_test->name);

	cr_assert(res == NULL, "[malloc off]Wrong return value got %p expected"
						   " %p.", res, NULL);
}

mmk_mock_define (malloc_mock_supervisor, void *, size_t);

mmk_no_optimize static void validate_calloc(size_t nmemb, size_t size)
{
	void *res;
	int supervisor_res;
	size_t byte_count, i;
	static char warned = false;
	static void *real_malloc = NULL;
	int cmp;

	if (real_malloc == NULL)
	{
		real_malloc = dlsym(RTLD_NEXT, "malloc");
		if (real_malloc == NULL)
			cr_fatal("Could not dlsym 'malloc'\n");
	}

	byte_count = nmemb * size;

	mmk_mock("malloc@self", malloc_mock_supervisor);
	mmk_when(malloc(mmk_any(size_t)), .then_call = real_malloc);
	res = ft_calloc(nmemb, size);
	supervisor_res = mmk_verify(malloc(mmk_eq(size_t, byte_count)), .times = 1);
	mmk_reset(malloc);

	cmp = 0;
	i = 0;
	while (i < byte_count)
	{
		if (((char *)res)[i] != 0)
		{
			cmp = ((char *)res)[i];
			break;
		}
		i++;
	}
	free(res);

	if (supervisor_res == 0 && warned == false)
	{
		cr_log_warn("(%s:%s) Unexpected malloc usage (either calling it too "
					"many, or too few times, or allocating too much or not "
					"enough memory)", criterion_current_suite
			->name, criterion_current_test->name);
		warned = true;
	}

	cr_assert(
		cmp == 0, "Function did not operate as expected. (memcmp = %d)", cmp);
}