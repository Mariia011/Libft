/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:46:42 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/01 12:03:45 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		cc;
	const unsigned char	*str;
	size_t				i;

	cc = (unsigned char)c;
	str = (const unsigned char *)s;
	if (!n)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (str[i] == cc)
		{
			return ((void *)str + i);
		}
		i++;
	}
	return (NULL);
}
