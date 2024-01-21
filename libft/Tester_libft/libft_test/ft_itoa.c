// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>
#include <mimick.h>

#include "utils/utils.h"

#define __USE_GNU
#include <dlfcn.h>

char *ft_itoa(int n);

typedef struct s_itoa_param
{
	int i;
	const char *result;
} t_itoa_param;

TestSuite(ft_itoa, .timeout=TIMEOUT);

ParameterizedTestParameters(ft_itoa, simple)
{
	static t_itoa_param data[] = {
		{.i = 0, .result = "0"},
		{.i = 42, .result = "42"},
		{.i = -42, .result = "-42"},
		{.i = 2147483647, .result = "2147483647"},
		{.i = -2147483648, .result = "-2147483648"},
	};

	return cr_make_param_array(t_itoa_param, data, sizeof(data) / sizeof
	(*data));
}

mmk_mock_define (malloc_mock_supervisor, void *, size_t);

ParameterizedTest(t_itoa_param *c, ft_itoa, simple)
{
	void *res;
	int cmp, supervisor_res;
	size_t malloc_size;
	static char warned = false;
	static void *real_malloc = NULL;

	if (real_malloc == NULL)
	{
		real_malloc = dlsym(RTLD_NEXT, "malloc");
		if (real_malloc == NULL)
			cr_fatal("Could not dlsym 'malloc'\n");
	}
	
	malloc_size = strlen(c->result) + 1;

	mmk_mock("malloc@self", malloc_mock_supervisor);
	mmk_when(malloc(mmk_any(size_t)), .then_call = real_malloc);
	res = ft_itoa(c->i);
	supervisor_res = mmk_verify(malloc(mmk_eq(size_t, malloc_size)), .times = 1);
	mmk_reset(malloc);

	cmp = strcmp(res, c->result);
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

mmk_mock_define (malloc_mock_fail, void *, size_t);

Test(ft_itoa, malloc_fail)
{
	void *res;
	int mimick_res;

	mmk_mock("malloc@self", malloc_mock_fail);
	mmk_when(malloc(mmk_any(size_t)), .then_return = NULL, .then_errno = ENOMEM);
	res = ft_itoa(354);
	mimick_res = mmk_verify(malloc(mmk_eq(size_t, 4)), .times = 1);
	mmk_reset(malloc);

	if (mimick_res == 0)
		cr_log_warn("(%s:%s) Unexpected malloc usage (either calling it too "
					"many, or too few times, or allocating too much or not "
					"enough memory", criterion_current_suite
			->name, criterion_current_test->name);

	cr_assert(res == NULL, "[malloc off]Wrong return value got %p expected"
						   " %p.", res, NULL);
}
