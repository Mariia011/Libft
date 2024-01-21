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

char *ft_strdup(const char *s);
static void validate_strdup(void *str, int f);

TestSuite(ft_strdup, .timeout=TIMEOUT);

Test(ft_strdup, string)
{
	char *str = "This is a test string";
	validate_strdup(str, false);
}

Test(ft_strdup, empty)
{
	char *str = "\0This is a test string";
	validate_strdup(str, false);
}

Test(ft_strdup, randomised)
{
	void *ptr0;
	int i, n;

	for (i = 0; i < RAND_ITERATIONS; i++)
	{
		n = (int)rand_number_max(500);
		rand_string(CHARSET_EXTENDED, n, &ptr0, NULL);

		validate_strdup(ptr0, true);
	}
}

mmk_mock_define (malloc_mock_fail, void *, size_t);

Test(ft_strdup, malloc_fail)
{
	char buf[5] = "....\0";
	void *res;
	int mimick_res;

	mmk_mock("malloc@self", malloc_mock_fail);
	mmk_when(malloc(mmk_any(size_t)), .then_return = NULL, .then_errno = ENOMEM);
	res = ft_strdup(buf);
	mimick_res = mmk_verify(malloc(mmk_eq(size_t, 5)), .times = 1);
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

mmk_no_optimize static void validate_strdup(void *str, int f)
{
	void *res0, *res1;
	int cmp, supervisor_res;
	size_t str_len;
	static char warned = false;
	static void *real_malloc = NULL;

	str_len = strlen(str);
	if (real_malloc == NULL)
	{
		real_malloc = dlsym(RTLD_NEXT, "malloc");
		if (real_malloc == NULL)
			cr_fatal("Could not dlsym 'malloc'\n");
	}

	res0 = strdup(str);

	mmk_mock("malloc@self", malloc_mock_supervisor);
	mmk_when(malloc(mmk_any(size_t)), .then_call = real_malloc);
	res1 = ft_strdup(str);
	supervisor_res = mmk_verify(malloc(mmk_eq(size_t, str_len + 1)), .times = 1);
	mmk_reset(malloc);

	if (res0 != NULL && res1 != NULL)
		cmp = memcmp(res0, res1, strlen(str) + 1);
	else
		cmp = -1;
	if (f == true)
		ft_free(str);
	free(res0);
	free(res1);

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