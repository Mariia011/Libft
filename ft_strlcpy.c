/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:01:39 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/31 17:20:53 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	min;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (ft_strlen(src));
	min = ft_min(dstsize - 1, src_len);
	while (i < min)
	{
		dst[i] = src[i];
		i++;
	}
	dst[min] = '\0';
	return (ft_strlen(src));
}
