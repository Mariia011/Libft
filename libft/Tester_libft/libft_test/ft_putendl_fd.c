// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>
#include <mimick.h>
#include <unistd.h>

#include "utils/utils.h"

void ft_putendl_fd(char *s, int fd);

typedef struct s_write_param
{
	char *str;
	size_t n;
} t_write_param;

typedef struct s_putstr_endl_param
{
	int fd;
	char *str;
	t_write_param result;
} t_putstr_endl_param;

TestSuite(ft_putendl_fd, .timeout=TIMEOUT);

ParameterizedTestParameters(ft_putendl_fd, simple)
{
	static t_putstr_endl_param data[] =
		{
			{
				.fd = 42,
				.str = "abcdef",
				.result =
					{
						.str = "abcdef\n",
						.n = 7,
					},
			},
			{
				.fd = -42,
				.str = "abc\ndef",
				.result =
					{
						.str = "abc\ndef\n",
						.n = 8,
					},
			},
			{
				.fd = 42,
				.str = "abc\ndef\n",
				.result =
					{
						.str = "abc\ndef\n\n",
						.n = 9,
					},
			},
			{
				.fd = 42,
				.str = "",
				.result =
					{
						.str = "\n",
						.n = 1,
					},
			},
		};

	return cr_make_param_array(t_putstr_endl_param, data,
		sizeof(data) / sizeof(*data));
}

static size_t g_write_len = 0;
static char *g_write_str = NULL;

static ssize_t mock_write(int fd, const void *buf, size_t n)
{
	(void)fd;
	g_write_str = realloc(g_write_str, g_write_len + n);
	memcpy(&g_write_str[g_write_len], buf, n);
	g_write_len += n;
	return (n);
}

mmk_mock_define (write_mock_supervisor, ssize_t, int, const void *, size_t);

ParameterizedTest(t_putstr_endl_param *param, ft_putendl_fd, simple)
{
	int supervisor_res, cmp;
	char *write_str_bak;
	size_t write_str_len;
	static int warned = false;

	mmk_mock("write@self", write_mock_supervisor);
	mmk_when(write(mmk_any(int), mmk_any(const void *), mmk_any(size_t)),
		.then_call  = (void (*)(void))&mock_write);
	ft_putendl_fd(param->str, param->fd);
	write_str_bak = g_write_str;
	write_str_len = g_write_len;
	g_write_str = NULL;
	g_write_len = 0;
	supervisor_res = mmk_verify(write(mmk_eq(int, param->fd), mmk_any
	(void *), mmk_eq(size_t, param->result.n - 1)), .times = 1);
	supervisor_res &= mmk_verify(write(mmk_eq(int, param->fd), mmk_any
	(void *), mmk_eq(size_t, 1)), .times = 1);
	mmk_reset(write);

	cmp = 0;
	if (write_str_bak != NULL)
		cmp = memcmp(write_str_bak, param->result.str, param->result.n);
	free(write_str_bak);

	cr_assert(write_str_bak != NULL, "Write not called\n");
	cr_assert(write_str_len == param->result.n, "Wrong write length got "
												  "%d expected %d.",
		write_str_len, param->result.n);
	if (supervisor_res == 0 && warned == false)
	{
		cr_log_warn("(%s:%s) Unexpected write usage (calling it with non "
					"optimised parameters, or incorrectly)", criterion_current_suite
			->name, criterion_current_test->name);
		warned = true;
	}
	cr_assert(cmp == 0, "Wrong string written.");
}
