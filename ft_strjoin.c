/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:47:16 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/01 17:01:37 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t	i;
    size_t	n;
    char	*strr;

    i = 0;
    n = 0;
    strr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (strr)
{
    while (s1[i] != '\0')
    {
        strr[i] = s1[i];
        i++;
    }
    n = i;
	i = 0;
    while (s2[i] != '\0')
    {
        strr[n] = s2[i];
        n++;
		i++;
    }
	strr[n] = '\0';
    return (strr);
}
    return (NULL);
}
