/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:33:04 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/27 14:26:17 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (!dst || !src)
		return (0);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	return (dst_len + ft_strlcpy(dst + dst_len, src, (dstsize - dst_len)));
}
