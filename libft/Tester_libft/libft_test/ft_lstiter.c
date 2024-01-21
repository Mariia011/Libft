// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>
#include <mimick.h>

#include "utils/utils.h"

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

void ft_lstiter(t_list *lst, void (*del)(void *));

TestSuite(ft_lstiter, .timeout=TIMEOUT);

static void **g_del_ptr = NULL;
static int g_del_called = 0;

static void func(void *ptr)
{
	g_del_ptr[g_del_called] = ptr;
	g_del_called++;
}

ParameterizedTestParameters(ft_lstiter, simple)
{
	static int data[] = { 1, 2, 3, 6, 9, 42 };

	return cr_make_param_array(int, data, sizeof(data) / sizeof
	(*data));
}

ParameterizedTest(int *c, ft_lstiter, simple)
{
	t_list *list;
	int i, j, found, size;
	int count;
	void **ptr;

	g_del_ptr = alloca(*c * sizeof(void *));

	i = 0;
	size = *c - 1;
	list = alloca(*c * sizeof(*list));
	while (i <= size)
	{
		list[i].content =(void *)(unsigned long long) size - i + 1;
		list[i].next = (i == 0 ? NULL : &(list[i - 1]));
		i++;
	}

	ft_lstiter(&list[size], &func);

	ptr = g_del_ptr;
	count = g_del_called;
	g_del_ptr = NULL;
	g_del_called = 0;

	cr_assert(count == size + 1, "Func called %d times expected %d",
		count, size + 1);
	i = 0;
	while (i <= size)
	{
		j = 0;
		found = false;
		while (j <= size)
		{
			if (ptr[j] == (void *)(unsigned long long)i + 1)
			{
				found = true;
				break;
			}
			j++;
		}
		i++;
		if (found == false)
			cr_assert(false, "Did apply to element %p.", i);
	}
}

Test(ft_lstiter, null)
{
	int count;

	ft_lstiter(NULL, &func);

	count = g_del_called;
	g_del_ptr = NULL;
	g_del_called = 0;

	cr_assert(count == 0, "Wrong func usage.");
}
