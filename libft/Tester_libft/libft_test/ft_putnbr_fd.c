// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>
#include <mimick.h>
#include <unistd.h>

#include "utils/utils.h"

void ft_putnbr_fd(int n, int fd);

typedef struct s_write_param
{
	char *str;
	size_t n;
} t_write_param;

typedef struct s_putnbr_fd_param
{
	int fd;
	int nbr;
	t_write_param result;
} t_putnbr_fd_param;

TestSuite(ft_putnbr_fd, .timeout=TIMEOUT);

ParameterizedTestParameters(ft_putnbr_fd, simple)
{
	static t_putnbr_fd_param data[] =
		{
			{
				.fd = 42,
				.nbr = 0,
				.result =
					{
						.str = "0",
						.n = 1,
					},
			},
			{
				.fd = -42,
				.nbr = -42,
				.result =
					{
						.str = "-42",
						.n = 3,
					},
			},
			{
				.fd = 42,
				.nbr = 42,
				.result =
					{
						.str = "42",
						.n = 2,
					},
			},
			{
				.fd = 42,
				.nbr = 2147483647,
				.result =
					{
						.str = "2147483647",
						.n = 10,
					},
			},
			{
				.fd = 42,
				.nbr = -2147483648,
				.result =
					{
						.str = "-2147483648",
						.n = 11,
					},
			},
		};

	return cr_make_param_array(t_putnbr_fd_param, data,
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

ParameterizedTest(t_putnbr_fd_param *param, ft_putnbr_fd, simple)
{
	int supervisor_res, cmp;
	char *write_str_bak;
	size_t write_str_len;
	static int warned = false;

	mmk_mock("write@self", write_mock_supervisor);
	mmk_when(write(mmk_any(int), mmk_any(const void *), mmk_any(size_t)),
		.then_call  = (void (*)(void))&mock_write);
	ft_putnbr_fd(param->nbr, param->fd);
	write_str_bak = g_write_str;
	write_str_len = g_write_len;
	g_write_str = NULL;
	g_write_len = 0;
	supervisor_res = mmk_verify(write(mmk_eq(int, param->fd), mmk_any
	(void *), mmk_eq(size_t, param->result.n)), .times
		= 1);
	mmk_reset(write);

	cmp = 0;
	if (write_str_bak != NULL)
		cmp = memcmp(write_str_bak, param->result.str, param->result.n);
	free(write_str_bak);

	cr_assert(write_str_bak != NULL, "Write not called\n");
	cr_assert(write_str_len == param->result.n, "Wrong write length got %d "
										 "expected %d.",
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
