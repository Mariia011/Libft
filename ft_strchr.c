/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:24:39 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/31 14:31:31 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	len; 	
	size_t	i;
	char*	ptr;

	ptr	= (char *)s;
	if (s != 0)
	{
		i = 0;
		len = strlen(s);
		while (i < len)
		{
			if (ptr[i] == c)
				return (ptr + i);
			i++;
		}
	}
return (NULL);
}
