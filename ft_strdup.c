/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:27:21 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/24 18:00:40 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*null_term;
	char	*tmp;

	if (src == 0)
		return (0);
	null_term = malloc(ft_strlen(src) + 1);
	tmp = null_term;
	while (*src != '\0')
	{
		*tmp = *src;
		src++;
		tmp++;
	}
	*tmp = *src;
	return (null_term);
}

