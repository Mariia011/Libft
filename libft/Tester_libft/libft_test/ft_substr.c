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

char *ft_substr(char const *s, unsigned int start, size_t len);

typedef struct s_substr_param
{
	char const *s;
	unsigned int start;
	size_t len;
} t_substr_param;

TestSuite(ft_substr, .timeout=TIMEOUT);

ParameterizedTestParameters(ft_substr, simple)
{
	static t_substr_param data[] = {
		{.s = "0123456789", .start = 1, .len = 3},
		{.s = "0123456789", .start = 5, .len = 10},
		{.s = "0123456789", .start = 10, .len = 3},
		{.s = "0123456789", .start = 9, .len = 10},
	};

	return cr_make_param_array(t_substr_param, data, sizeof(data) / sizeof
	(*data));
}

mmk_mock_define (malloc_mock_supervisor, void *, size_t);

ParameterizedTest(t_substr_param *c, ft_substr, simple)
{
	void *res;
	int cmp, last_byte, supervisor_res;
	size_t str_len, malloc_size;
	static char warned = false;
	static void *real_malloc = NULL;

	if (real_malloc == NULL)
	{
		real_malloc = dlsym(RTLD_NEXT, "malloc");
		if (real_malloc == NULL)
			cr_fatal("Could not dlsym 'malloc'\n");
	}

	str_len = strlen(&c->s[c->start]);
	malloc_size = (str_len > c->len ? (size_t)c->len : str_len) + 1;

	mmk_mock("malloc@self", malloc_mock_supervisor);
	mmk_when(malloc(mmk_any(size_t)), .then_call = real_malloc);
	res = ft_substr(c->s, c->start, c->len);
	supervisor_res = mmk_verify(malloc(mmk_eq(size_t, malloc_size)), .times = 1);
	mmk_reset(malloc);

	cmp = memcmp(res, &c->s[c->start], malloc_size - 1);
	last_byte = ((char *)res)[malloc_size - 1] == '\0';
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
	cr_assert(last_byte, "Function did not null terminate the string");
}

mmk_mock_define (malloc_mock_fail, void *, size_t);

Test(ft_substr, malloc_fail)
{
	char *buf = "0123456789";
	void *res;
	int mimick_res;

	mmk_mock("malloc@self", malloc_mock_fail);
	mmk_when(malloc(mmk_any(size_t)), .then_return = NULL, .then_errno = ENOMEM);
	res = ft_substr(buf, 2, 15);
	mimick_res = mmk_verify(malloc(mmk_eq(size_t, 9)), .times = 1);
	mmk_reset(malloc);

	if (mimick_res == 0)
		cr_log_warn("(%s:%s) Unexpected malloc usage (either calling it too "
					"many, or too few times, or allocating too much or not "
					"enough memory", criterion_current_suite
			->name, criterion_current_test->name);

	cr_assert(res == NULL, "[malloc off]Wrong return value got %p expected"
						   " %p.", res, NULL);
}

Test(ft_substr, edge_case)
{
	void *res;
	char c;

	res = ft_substr("0123456789", 15, 5);
	if (res != NULL)
		c = ((char *)res)[0];
	free(res);

	cr_assert(res != NULL, "Wrong return value got %p expected %p.", res, NULL);
	cr_assert(c == '\0', "Wrong char got %d expected %d.", c, '\0');
}