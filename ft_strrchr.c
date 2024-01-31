/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:05:49 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/31 14:34:47 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	i = ft_strlen(s) + 1;
	char *ptr;
	ptr = (char *)s;
	if(s != 0)
	{
	while(i >= 0)
	{
		if(ptr[i] == c)
			return (ptr + i);
		i--;
	}
	}
	return(NULL);
}
