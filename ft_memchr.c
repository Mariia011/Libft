/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:46:42 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/27 14:49:40 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char cc = (unsigned char)c;
	const unsigned char *str = (const unsigned char *)s;
	size_t i;
	if(!n)
		return(NULL);
	i = 0;
	while(i < n)
	{
		if(str[i] == cc)
		{
			return((void *)str + i);
		}	
		i++;
	} 
	return(NULL);
}
