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

char *ft_strmapi(char const *s, char (*f)(unsigned int, char));

typedef struct s_strmapi_param
{
	char const *str;
	char const *result;
	char (*f)(unsigned int, char);
} t_strmapi_param;

static char f1(unsigned int i, char c)
{
	return (char)(((int)c + i) % 128);
}

TestSuite(ft_strmapi, .timeout=TIMEOUT);

ParameterizedTestParameters(ft_strmapi, simple)
{
	static t_strmapi_param data[] = {
		{.str = "abcdef", .result = "acegik", .f = &f1},
		{.str = "", .result = "", .f = &f1},
		{.str = "aaaa", .result = "abcd", .f = &f1},
		{.str = "a", .result = "a", .f = &f1},
	};

	return cr_make_param_array(t_strmapi_param, data,
		sizeof(data) / sizeof(*data));
}

mmk_mock_define (malloc_mock_supervisor, void *, size_t);

ParameterizedTest(t_strmapi_param *c, ft_strmapi, simple)
{
	void *res;
	int cmp, supervisor_res;
	size_t result_size;
	static char warned = false;
	static void *real_malloc = NULL;

	if (real_malloc == NULL)
	{
		real_malloc = dlsym(RTLD_NEXT, "malloc");
		if (real_malloc == NULL)
			cr_fatal("Could not dlsym 'malloc'\n");
	}

	result_size = strlen(c->result) + 1;
	mmk_mock("malloc@self", malloc_mock_supervisor);
	mmk_when(malloc(mmk_any(size_t)), .then_call = real_malloc);
	res = ft_strmapi(c->str, c->f);
	supervisor_res = mmk_verify(malloc(mmk_eq(size_t, result_size)), .times = 1);
	mmk_reset(malloc);

	if (supervisor_res == 0 && warned == false)
	{
		cr_log_warn("(%s:%s) Unexpected malloc usage (either calling it too "
					"many, or too few times, or allocating too much or not "
					"enough memory)", criterion_current_suite
			->name, criterion_current_test->name);
		warned = true;
	}

	cmp = memcmp(res, c->result, result_size);
	free(res);

	cr_assert(
		cmp == 0, "Function did not operate as expected. (memcmp = %d)", cmp);
}

mmk_mock_define (malloc_mock_fail, void *, size_t);

static int called = 0;

static char f1_fail(unsigned int i, char c)
{
	(void)i;
	(void)c;
	called++;
	return 0;
}

Test(ft_strmapi, malloc_fail)
{
	char *s1 = "abcdef";
	void *res;

	int mimick_res;

	mmk_mock("malloc@self", malloc_mock_fail);
	mmk_when(malloc(mmk_any(size_t)), .then_return = NULL, .then_errno = ENOMEM);
	res = ft_strmapi(s1, &f1_fail);
	mimick_res = mmk_verify(malloc(mmk_eq(size_t, strlen(s1) + 1)), .times = 1);
	mmk_reset(malloc);

	if (mimick_res == 0)
		cr_log_warn("(%s:%s) Unexpected malloc usage (either calling it too "
					"many, or too few times, or allocating too much or not "
					"enough memory", criterion_current_suite
			->name, criterion_current_test->name);
	if (called > 0)
		cr_log_warn("(%s:%s) [malloc off] Function f was called %d time(s).",
			criterion_current_suite
			->name, criterion_current_test->name, called);
	called = false;

	cr_assert(res == NULL, "[malloc off]Wrong return value got %p expected"
						   " %p.", res, NULL);
}
