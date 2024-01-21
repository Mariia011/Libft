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

void ft_lstadd_back(t_list **lst, t_list *new);

TestSuite(ft_lstadd_back, .timeout=TIMEOUT);

ParameterizedTestParameters(ft_lstadd_back, simple)
{
	static int data[] = { 1, 2, 3, 6, 9, 42 };

	return cr_make_param_array(int, data, sizeof(data) / sizeof
	(*data));
}

ParameterizedTest(int *c, ft_lstadd_back, simple)
{
	t_list *list, add;
	int i;
	t_list *current;

	add.content = CANARY;
	add.next = CANARY;
	list = alloca(sizeof(t_list) * *c);
	i = 0;
	*c = *c - 1;
	while (i <= *c)
	{
		list[i].next = (i == *c ? NULL : &list[i + 1]);
		list[i].content = (void *)(unsigned long long)i;
		i++;
	}
	ft_lstadd_back(&list, &add);
	current = list;
	i = 0;
	while (i <= *c)
	{
		cr_assert(current == &list[i],
			"The list has been changed: element in place %d have address %p "
			"but %p was expected.", i, current, &list[i]);
		cr_assert(current->content == (void *)(unsigned long long)i,
			"Wrong element in place %d got %p expected %p.", i, current
			->content, i);
		current = current->next;
		i++;
	}
	cr_assert(current != NULL, "No element added.");
	cr_assert(current->content == CANARY,
		"Wrong element added got %p expected %p.", current->content, CANARY);
	cr_assert(current->next == CANARY,
		"Wrong element added got next=%p expected next=%p.", current->next,
		CANARY);
}

Test(ft_lstadd_back, ptr_to_null)
{
	t_list *parent_ptr = NULL;
	t_list child = { .content = (void *)42, .next = NULL };

	ft_lstadd_back(&parent_ptr, &child);

 		cr_assert(parent_ptr == &child, "new should be the new parent, got %p "
													 "expected %p.", parent_ptr, &child);
	cr_assert(parent_ptr->content == (void *)42, "Wrong content got %p "
												 "expected %p.", (*parent_ptr)
		.content, 42);
	cr_assert(parent_ptr->next == NULL, "Wrong next element at the end of"
										" the list got %p expected %p.",
		(*parent_ptr).next, NULL);
}
