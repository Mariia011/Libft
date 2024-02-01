/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:17:30 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/01 13:38:06 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;
	char	*ptr;
	char	*ptr2;

	ptr = (char *)dst;
	ptr2 = (char *)src;
	if (!src && !dst && len)
		return (NULL);
	if (dst < src)
	{
		ft_memcpy(dst, src, len);
	}
	else
	{
		i = ((int)len) - 1;
		while (i >= 0)
		{
			ptr[i] = ptr2[i];
			i--;
		}
	}
	return (dst);
}
