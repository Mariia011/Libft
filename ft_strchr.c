/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:24:39 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/27 14:23:06 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char*	ptr;

	ptr	= (char *)s;
	if (s != 0)
	{
		i = 0;
		while (ptr[i] != '\0')
		{
			if (ptr[i] == c)
				return (ptr + i);
			i++;
		}
	}
	return (NULL);
}
