/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:43:20 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/01 12:06:53 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*s_1;
	char	*s_2;

	i = 0;
	s_1 = (char *)s1;
	s_2 = (char *)s2;
	if (!n)
		return (0);
	while (i < n - 1)
	{
		if (s_1[i] != s_2[i])
			break ;
		i++;
	}
	return ((unsigned char)s_1[i] - (unsigned char)s_2[i]);
}
