/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:47:43 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/01 11:42:11 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(size_t count, size_t size)
{
	return (((long long)count < 0 && (long long)size != 0)
		|| ((long long)count != 0 && (long long)size < 0)
		|| ((long long)count >= INT_MAX || (long long)size >= INT_MAX));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*new_call;

	if (ft_check(count, size))
		return (NULL);
	new_call = malloc(count * size);
	if (!new_call)
		return (NULL);
	return (ft_memset(new_call, 0, count * size));
}
