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

void ft_lstclear(t_list **lst, void (*del)(void *));

TestSuite(ft_lstclear, .timeout=TIMEOUT);

static void **g_del_ptr = NULL;
static int g_del_called = 0;

static void del(void *ptr)
{
	g_del_ptr[g_del_called] = ptr;
	g_del_called++;
}

ParameterizedTestParameters(ft_lstclear, simple)
{
	static int data[] = { 1, 2, 3, 6, 9, 42 };

	return cr_make_param_array(int, data, sizeof(data) / sizeof
	(*data));
}

ParameterizedTest(int *c, ft_lstclear, simple)
{
	t_list *list, *current;
	int i, j, found, size;
	int count;
	void **ptr;

	g_del_ptr = alloca(*c * sizeof(void *));

	i = 0;
	size = *c - 1;
	current = malloc(sizeof(*current));
 	if (current == NULL)
		cr_fail("Could not malloc test data.");
	list = current;
	while (i < size)
	{
		if (current == NULL)
		{
			current = list;
			while (current != NULL)
			{
				current = current->next;
				free(list);
				list = current;
			}
			cr_fail("Could not malloc test data.");
		}
		current->content =(void *)(unsigned long long) size - i + 1;
		current->next = malloc(sizeof(*current));
		current = current->next;
		i++;
	}
	current->next = NULL;
	current->content = (void *)(unsigned long long) size - i + 1;

	ft_lstclear(&list, &del);

	ptr = g_del_ptr;
	count = g_del_called;
	g_del_ptr = NULL;
	g_del_called = 0;

	cr_assert(count == size + 1, "Del called %d times expected %d",
		count, size + 1);
	cr_assert(list == NULL, "Initial pointer got %p expected %p.", list, NULL);
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
			cr_assert(false, "Did not free element %p.", i);
	}
}

Test(ft_lstclear, null_content)
{
	t_list *lst;
	int count;

	lst = NULL;

	ft_lstclear(&lst, &del);

	count = g_del_called;
	g_del_ptr = NULL;
	g_del_called = 0;

	cr_assert(count == 0, "Wrong del usage.");
}
