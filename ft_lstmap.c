/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:10:38 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/07 19:01:42 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	_lstmap(t_list *other, t_list **head, void *(*f)(void *),
		void (*del)(void *))
{
	if (!other)
		return ;
	*head = ft_lstnew(f(other->content));
	_lstmap(other->next, &((*head)->next), f, del);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	_lstmap(lst, &head, f, del);
	return (head);
}
