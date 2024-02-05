/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:05:40 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/05 17:26:53 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*ssr;

	if (!lst || !del)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		ssr = temp->next;
		del(ssr->content);
		free(ssr);
		temp = ssr;
	}
	*lst = NULL;
	return ;
}
