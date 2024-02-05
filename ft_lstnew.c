/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:11:23 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/05 17:27:13 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_one;

	new_one = malloc(sizeof(t_list));
	if (!new_one)
		return (NULL);
	new_one->content = content;
	new_one->next = NULL;
	return (new_one);
}
