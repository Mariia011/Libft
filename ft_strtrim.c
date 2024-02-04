/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:49:56 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/04 20:13:15 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*malloc_str(char *str)
{
	char	*str;

}

char *ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	size_t end;

	if (!s1)
		return (NULL);
	start = 0;
	len = 0;
//	end = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
//	if (s1[i] == '\0')
	end = ft_strlen(s1) - 1;
	while (end > start && )
	return (str);
}
