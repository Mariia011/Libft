/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:05:40 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/07 17:32:54 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cccp;

	if (!lst || !(*lst) || !del)
		return ;
	while (*lst != NULL)
	{
		cccp = ((*lst)->next);
		ft_lstdelone((*lst), del);
		(*lst) = cccp;
	}
	return ;
}
