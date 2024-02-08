/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:17:45 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/07 17:19:54 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill(char const *s, size_t len)
{
	char	*str;

	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	return (ft_memmove(str, s, len));
}

static int	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	new_len;

	if (!s)
		return (NULL);
	new_len = ft_strlen(s);
	if (start >= new_len)
		return (ft_strdup(""));
	return (fill(s + start, min(len, new_len - start)));
}
