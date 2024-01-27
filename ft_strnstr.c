/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:25:14 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/27 14:20:13 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	_ft_min(size_t a, size_t b)
{
	if (b > a)
		return (a);
	return (b);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	lim;
	size_t	i;
	size_t	len_hstk;
	size_t	len_ndl;

	if (!haystack && !len)
		return ((char *)haystack);
	len_hstk = ft_strlen(haystack);
	len_ndl = ft_strlen(needle);
	lim = _ft_min(len, len_hstk);
	if (len_ndl <= lim)
	{
		i = 0;
		while (i <= (lim - len_ndl))
		{
			if (!strncmp(haystack + i, needle, len_ndl))
				return ((char *)haystack + i);
			i++;
		}
	}
	return (0);
}