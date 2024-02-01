/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:25:14 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/01 14:34:22 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	_min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	size;
	size_t	i;
	size_t	len_ofhay;
	size_t	len_ndl;

	if (!haystack && !len)
		return ((char *)haystack);
	len_ofhay = ft_strlen(haystack);
	len_ndl = ft_strlen(needle);
	size = _min(len, len_ofhay);
	if (len_ndl <= size)
	{
		i = 0;
		while (i <= (len - len_ndl))
		{
			if (!ft_strncmp(haystack + i, needle, len_ndl))
				return ((char *)haystack + i);
			i++;
		}
	}
	return (0);
}
