/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:27:21 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/01 13:54:10 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*null_term;
	char	*tmp;

	null_term = malloc(ft_strlen(src) + 1);
	if (!null_term)
		return (NULL);
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
