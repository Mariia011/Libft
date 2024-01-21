// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>

#include "utils/utils.h"

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

int ft_lstsize(t_list *lst);

TestSuite(ft_lstsize, .timeout=TIMEOUT);

ParameterizedTestParameters(ft_lstsize, simple)
{
	static int data[] = { 1, 2, 3, 6, 9, 42 };

	return cr_make_param_array(int, data, sizeof(data) / sizeof
	(*data));
}

ParameterizedTest(int *c, ft_lstsize, simple)
{
	t_list *list;
	int i, size;

	list = alloca(sizeof(t_list) * *c);
	i = 0;
	*c = *c - 1;
	while (i <= *c)
	{
		list[i].next = (i == *c ? NULL : &list[i + 1]);
		i++;
	}
	size = ft_lstsize(list);
	*c = *c + 1;
	cr_assert(size == *c, "Wrong size got %d expected %d.", size, *c);
}

Test(ft_lstsize, null)
{
	int size;

	size = ft_lstsize(NULL);
	cr_assert(size == 0, "Wrong size got %d expected %d.", size, 0);
}
