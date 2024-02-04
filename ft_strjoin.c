/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:47:16 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/02 12:27:07 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*add(char *str, char *str2)
{
	size_t	index;
	size_t	len;

	if (str)
	{
		index = 0;
		len = ft_strlen(str);
		while (str2[index])
		{
			str[len] = str2[index];
			len++;
			index++;
		}
		str[len] = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	strr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (strr)
	{
		strr[0] = '\0';
		strr = add(add(strr, (char *)s1), (char *)s2);
		return (strr);
	}
	return (NULL);
}
