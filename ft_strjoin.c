/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:47:16 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/30 10:47:58 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strjoin(char const *s1, char const *s2)
{
    size_t i;
    size_t n;
    char *strr;
    i = 0;
    n = 0;
    strr = (char *)malloc(sizeof(ft_strlen(s1) + sizeof(ft_strlen(s2)) + 1));
    if (strr)
{
    while(s1)
    {
        strr[i] = s1[i];
        i++;
    }
    i = n;
    while(s2 != '\0')
    {
        i = 0;
        n++;
        strr[n] = s2[i];
        i++;
    }
    return (strr);
}        
    return (NULL); 
}