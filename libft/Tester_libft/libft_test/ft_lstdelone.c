// SPDX-FileCopyrightText: 2020 The at42 Libft Unit Tests Contributors (see CONTRIBUTORS.md)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>
#include <mimick.h>

#include "utils/utils.h"

#define  CONTENT (void *)0x41424344
#define  NEXT (void *)0x40414243

typedef struct s_list
{
	void *content;
	struct s_list *next;
} t_list;

void ft_lstdelone(t_list *lst, void (*del)(void *));

TestSuite(ft_lstdelone, .timeout=TIMEOUT);

static void *g_del_ptr = NULL;
static int g_del_called = 0;

static void del(void *ptr)
{
	g_del_ptr = ptr;
	g_del_called++;
}

Test(ft_lstdelone, simple)
{
	t_list *lst;
	void *ptr;
	int count;

	lst = malloc(sizeof(*lst));
	if (lst == NULL)
		cr_fail("Could not malloc test data.");
	lst->content = CONTENT;
	lst->next = NEXT;

	ft_lstdelone(lst, &del);

	count = g_del_called;
	ptr = g_del_ptr;
	g_del_ptr = NULL;
	g_del_called = 0;

	cr_assert(ptr == CONTENT && count == 1, "Wrong del usage.");
}

Test(ft_lstdelone, null_content)
{
	t_list *lst;
	int count;

	lst = malloc(sizeof(*lst));
	if (lst == NULL)
		cr_fail("Could not malloc test data.");
	lst->content = NULL;
	lst->next = NEXT;

	ft_lstdelone(lst, &del);

	count = g_del_called;
	g_del_ptr = NULL;
	g_del_called = 0;

	cr_assert(count == 0, "Wrong del usage.");
}

Test(ft_lstdelone, null)
{
	int count;

	ft_lstdelone(NULL, &del);

	count = g_del_called;
	g_del_ptr = NULL;
	g_del_called = 0;

	cr_assert(count == 0, "Wrong del usage.");
}
