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

void ft_lstadd_front(t_list **lst, t_list *new);

TestSuite(ft_lstadd_front, .timeout=TIMEOUT);

Test(ft_lstadd_front, simple)
{
	t_list *parent_ptr;
	t_list parent = { .content = (void *)42, .next = NULL };
	t_list child = { .content = (void *)41, .next = NULL };
	parent_ptr = &parent;

	ft_lstadd_front(&parent_ptr, &child);

		cr_assert(parent_ptr == &child, "Wrong list begin got %p "
													 "expected %p.", parent_ptr, &child);
	cr_assert(parent_ptr->content == (void *)41, "Wrong list begin content got %p "
												 "expected %p.", parent_ptr
		->content, 41);
	cr_assert(parent_ptr->next == &parent, "The old parent element isn't "
		"following the new parent.");
	cr_assert(
		parent_ptr->next->content == (void *)42, "Wrong list begin: got %p "
												 "expected %p.", parent_ptr
		->content, 42);
	cr_assert(parent_ptr->next->next == NULL, "Wrong next element at the end of"
											  " the list got %p expected %p.",
		parent_ptr->next->next, NULL);
}

Test(ft_lstadd_front, ptr_to_null)
{
	t_list *parent_ptr = NULL;
	t_list child = { .content = (void *)42, .next = NULL };

	ft_lstadd_front(&parent_ptr, &child);

	cr_assert(parent_ptr == &child, "Wrong first element of the list "
										"got %p expected %p.",
		parent_ptr, &child);

	cr_assert(parent_ptr->content == (void *)42, "Wrong list content got %p "
												 "expected %p.", (*parent_ptr)
		.content, 42);
	cr_assert(parent_ptr->next == NULL, "Wrong next element at the end of"
										" the list got %p expected %p.",
		(*parent_ptr).next, NULL);
}
