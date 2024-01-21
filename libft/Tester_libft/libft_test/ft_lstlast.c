// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>

#include "utils/utils.h"

#define  CANARY (void *)0x41424344

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

t_list *ft_lstlast(t_list *lst);

TestSuite(ft_lstlast, .timeout=TIMEOUT);

ParameterizedTestParameters(ft_lstlast, simple)
{
	static int data[] = { 1, 2, 3, 6, 9, 42 };

	return cr_make_param_array(int, data, sizeof(data) / sizeof
	(*data));
}

ParameterizedTest(int *c, ft_lstlast, simple)
{
	t_list *list;
	int i;
	t_list *ret;

	list = alloca(sizeof(t_list) * *c);
	i = 0;
	*c = *c - 1;
	while (i <= *c)
	{
		list[i].next = (i == *c ? NULL : &list[i + 1]);
		list[i].content = (i == *c ? CANARY : (void *)0);
		i++;
	}
	ret = ft_lstlast(list);
	cr_assert(ret->content == CANARY, "Wrong element got %p expected %p.",
		ret->content, CANARY);
}

Test(ft_lstlast, null)
{
	void *res;

	res = ft_lstlast(NULL);
	cr_assert(res == NULL, "Wrong last element got %p expected %p.", res, NULL);
}
