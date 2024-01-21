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

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

t_list *ft_lstnew(void *content);

TestSuite(ft_lstnew, .timeout=TIMEOUT);

ParameterizedTestParameters(ft_lstnew, simple)
{
	static void *data[] = { (void *)0, (void *)1, (void *)2 };

	return cr_make_param_array(void *, data, sizeof(data) / sizeof(*data));
}

mmk_mock_define (malloc_mock_supervisor, void *, size_t);

ParameterizedTest(void **c, ft_lstnew, simple)
{
	t_list *res;
	void *data, *next;
	int supervisor_res;
	size_t malloc_size;
	static char warned = false;
	static void *real_malloc = NULL;

	if (real_malloc == NULL)
	{
		real_malloc = dlsym(RTLD_NEXT, "malloc");
		if (real_malloc == NULL)
			cr_fatal("Could not dlsym 'malloc'\n");
	}

	malloc_size = sizeof(t_list);

	mmk_mock("malloc@self", malloc_mock_supervisor);
	mmk_when(malloc(mmk_any(size_t)), .then_call = real_malloc);
	res = ft_lstnew(*c);
	supervisor_res = mmk_verify(malloc(mmk_eq(size_t, malloc_size)), .times = 1);
	mmk_reset(malloc);

	data = res->content;
	next = res->next;
	free(res);

	if (supervisor_res == 0 && warned == false)
	{
		cr_log_warn("(%s:%s) Unexpected malloc usage (either calling it too "
					"many, or too few times, or allocating too much or not "
					"enough memory)", criterion_current_suite
			->name, criterion_current_test->name);
		warned = true;
	}

	cr_assert(data == *c, "Wrong content got %p expected %p", data, *c);
	cr_assert(next == NULL, "Wrong next got %p expected %p", next, NULL);
}

mmk_mock_define (malloc_mock_fail, void *, size_t);

Test(ft_lstnew, malloc_fail)
{
	void *res;
	int mimick_res;

	mmk_mock("malloc@self", malloc_mock_fail);
	mmk_when(malloc(mmk_any(size_t)), .then_return = NULL, .then_errno = ENOMEM);
	res = ft_lstnew((void *)42);
	mimick_res = mmk_verify(malloc(mmk_eq(size_t, sizeof(t_list))),
		.times = 1);
	mmk_reset(malloc);

	if (mimick_res == 0)
		cr_log_warn("(%s:%s) Unexpected malloc usage (either calling it too "
					"many, or too few times, or allocating too much or not "
					"enough memory", criterion_current_suite
			->name, criterion_current_test->name);

	cr_assert(res == NULL, "[malloc off]Wrong return value got %p expected"
						   " %p.", res, NULL);
}
