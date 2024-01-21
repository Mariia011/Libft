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

char *ft_strjoin(char const *s1, char const *s2);

typedef struct s_strjoin_param
{
	char const *s1;
	char const *s2;
	char const *result;
} t_strjoin_param;

TestSuite(ft_strjoin, .timeout=TIMEOUT);

ParameterizedTestParameters(ft_strjoin, simple)
{
	static t_strjoin_param data[] = {
		{.s1 = "abcdef", .s2 = "ghi", .result = "abcdefghi"},
		{.s1 = "abcdef", .s2 = "", .result = "abcdef"},
		{.s1 = "", .s2 = "", .result = ""},
		{.s1 = "", .s2 = "a", .result = "a"},
		{.s1 = "ghi", .s2 = "abcdef", .result = "ghiabcdef"},
	};

	return cr_make_param_array(t_strjoin_param, data,
		sizeof(data) / sizeof(*data));
}

mmk_mock_define (malloc_mock_supervisor, void *, size_t);

ParameterizedTest(t_strjoin_param *c, ft_strjoin, simple)
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
	res = ft_strjoin(c->s1, c->s2);
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

Test(ft_strjoin, malloc_fail)
{
	char *s1 = "01234";
	char *s2 = "56789";
	void *res;
	int mimick_res;

	mmk_mock("malloc@self", malloc_mock_fail);
	mmk_when(malloc(mmk_any(size_t)), .then_return = NULL, .then_errno = ENOMEM);
	res = ft_strjoin(s1, s2);
	mimick_res = mmk_verify(malloc(mmk_eq(size_t, 11)), .times = 1);
	mmk_reset(malloc);

	if (mimick_res == 0)
		cr_log_warn("(%s:%s) Unexpected malloc usage (either calling it too "
					"many, or too few times, or allocating too much or not "
					"enough memory", criterion_current_suite
			->name, criterion_current_test->name);

	cr_assert(res == NULL, "[malloc off]Wrong return value got %p expected"
						   " %p.", res, NULL);
}
