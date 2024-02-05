/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:35:04 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/05 17:27:37 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	dgt_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static int	count_size(int n)
{
	return (dgt_count(n) + (n < 0));
}

static char	fill_malloc(int n)
{
	if (n < 0)
		n *= -1;
	return ((n % 10) + '0');
}

static char	*malloc_str(int n)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	size = count_size(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	if (n < 0)
	{
		str[i] = '-';
		i++;
	}
	while (size > i)
	{
		size--;
		str[size] = fill_malloc(n);
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	return (malloc_str(n));
}
