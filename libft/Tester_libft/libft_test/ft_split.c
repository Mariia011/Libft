// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>
#include <mimick.h>

#include "utils/utils.h"
#include <string.h>

#define __USE_GNU
#include <dlfcn.h>

char **ft_split(char const *s, char c);

struct ft_split_param
{
	char *s;
	char c;
	char **ret_exp;
};

TestSuite(ft_split, .timeout = TIMEOUT);

static char *ret0[] = {"This is a string", NULL};
static char *ret1[] = {"This", "is", "a", "string", NULL};
static char *ret2[] = {"his is the string", NULL};
static char *ret3[] = {"This is the strin", NULL};
static char *ret_null[] = {NULL};
static char *ret5[] = {"This is a string", NULL};
static char *ret6[] = {"This", "is", "a", "string", NULL};

static struct ft_split_param params[] = {{
											 .s = "This is a string",
											 .c = '@',
											 .ret_exp = ret0,
										 },
										 {
											 .s = "This is a string",
											 .c = ' ',
											 .ret_exp = ret1,
										 },
										 {
											 .s = "This is the string",
											 .c = 'T',
											 .ret_exp = ret2,
										 },
										 {
											 .s = "This is the string",
											 .c = 'g',
											 .ret_exp = ret3,
										 },
										 {
											 .s = "",
											 .c = '@',
											 .ret_exp = ret_null,
										 },
										 {
											 .s = "This is a string",
											 .c = '\0',
											 .ret_exp = ret5,
										 },
										 {
											 .s = "@",
											 .c = '@',
											 .ret_exp = ret_null,
										 },
										 {
											 .s = "@@@@@",
											 .c = '@',
											 .ret_exp = ret_null,
										 },
										 {
											 .s = "  This  is   a   string  ",
											 .c = ' ',
											 .ret_exp = ret6,
										 }};

ParameterizedTestParameters(ft_split, simple)
{
	return cr_make_param_array(struct ft_split_param, params,
							   sizeof(params) / sizeof(*params));
}

mmk_mock_define(malloc_mock_supervisor, void *, size_t);

ParameterizedTest(struct ft_split_param *param, ft_split, simple)
{
	int i;
	char **ret_ft;
	int malloc_supervisor_res = true;
	static char malloc_warned = false;
	static void *real_malloc = NULL;

	if (real_malloc == NULL)
	{
		real_malloc = dlsym(RTLD_NEXT, "malloc");
		if (real_malloc == NULL)
			cr_fatal("Could not dlsym 'malloc'\n");
	}

	mmk_mock("malloc@self", malloc_mock_supervisor);
	mmk_when(malloc(mmk_any(size_t)), .then_call = real_malloc);
	ret_ft = ft_split(param->s, param->c);
	for (i = 0; param->ret_exp[i] != NULL; i++)
	{
		malloc_supervisor_res &= mmk_verify(
			malloc(mmk_eq(size_t, strlen(param->ret_exp[i]) + 1)), .times = 1);
	}
	malloc_supervisor_res &= mmk_verify(
		malloc(mmk_eq(size_t, sizeof(void *) * (i + 1))), .times = 1);
	mmk_reset(malloc);

	cr_assert(ret_ft != NULL,
			  "Returns NULL expected a valid pointer to an array.");
	for (i = 0; ret_ft[i] != NULL && param->ret_exp[i] != NULL; i++)
	{
		cr_expect(
			strcmp(ret_ft[i], param->ret_exp[i]) == 0,
			"returned_array[%d] contains \"%s\" but should contains \"%s\".", i,
			ret_ft[i], param->ret_exp[i]);
		free(ret_ft[i]);
	}
	cr_expect(ret_ft[i] == NULL && param->ret_exp[i] == NULL,
			  "Returned array has too few or too much elements.");
	free(ret_ft);

	if (malloc_supervisor_res == 0 && malloc_warned == false)
	{
		cr_log_warn(
			"(%s:%s) Unexpected malloc usage (either calling it too many, or "
			"too few times, or allocating too much or not enough memory).",
			criterion_current_suite->name, criterion_current_test->name);
		malloc_warned = true;
	}
}

ParameterizedTestParameters(ft_split, malloc_fail)
{
	return cr_make_param_array(struct ft_split_param, params,
							   sizeof(params) / sizeof(*params));
}

static void validate_split_malloc_fail(char *s, char c, int target);

ParameterizedTest(struct ft_split_param *param, ft_split, malloc_fail)
{
	for (int target = 0; param->ret_exp[target] != NULL; target++)
		validate_split_malloc_fail(param->s, param->c, target);
}

static int g_target;
static int g_times_malloc_called;

static void *malloc_fail_target(size_t n)
{
	static void *(*real_malloc)(size_t) = NULL;

	if (real_malloc == NULL)
	{
		real_malloc = dlsym(RTLD_NEXT, "malloc");
		if (real_malloc == NULL)
			cr_fatal("Could not dlsym 'malloc'\n");
	}

	if (g_times_malloc_called >= g_target)
		return (NULL);
	g_times_malloc_called++;
	return (real_malloc(n));
}

static void validate_split_malloc_fail(char *s, char c, int target)
{
	char **ret_ft;
	int malloc_supervisor_res;
	static char malloc_warned = false;

	g_target = target;
	g_times_malloc_called = 0;

	mmk_mock("malloc@self", malloc_mock_supervisor);
	mmk_when(malloc(mmk_any(size_t)), .then_call = (void *)malloc_fail_target);
	ret_ft = ft_split(s, c);
	malloc_supervisor_res =
		mmk_verify(malloc(mmk_any(size_t)), .times = target + 1);
	mmk_reset(malloc);

	cr_assert(ret_ft == NULL, "[malloc off]Returns %p but NULL expected.",
			  ret_ft);

	if (malloc_supervisor_res == 0 && malloc_warned == false)
	{
		cr_log_warn(
			"(%s:%s) Unexpected malloc usage (either calling it too many, or "
			"too few times, or allocating too much or not enough memory).",
			criterion_current_suite->name, criterion_current_test->name);
		malloc_warned = true;
	}
}
