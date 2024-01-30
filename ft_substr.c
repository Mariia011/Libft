/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:17:45 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/30 13:56:03 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *fill(char const *s, unsigned int start, size_t len)
{
    char    *new_str;
    size_t  i;
    i = 0;
    new_str = (char *)malloc(ft_strlen(s) + 1);
    while(i < len)
    {
       new_str[i] = s[start + i];
       i++;
    }
    if(new_str)
        return (new_str);
    return (NULL);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    size_t  s_len;
    s_len = ft_strlen(s);
    if(s_len <= start || s_len < start + len)
        return (NULL);
    return (fill(s, start, len));
}