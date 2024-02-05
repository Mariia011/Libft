/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:34:09 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/05 19:45:53 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char const c)
{
	int	word;
	int	flag;
	int	i;

	word = 0;
	i = 0;
	while (str)
	{
		flag = 0;
		if(str[i] != c)
			flag = 0;
		if(str[i] == c && flag)
		{
			flag = ;
		}

	}
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
}
