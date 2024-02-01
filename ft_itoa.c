/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:35:04 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/01 17:41:18 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t _dig_count(int n)
{
    size_t  count;

    count = 0;
    while (n != 0)
    {
        n /= 10;
        count++;
    }
    return (count);
}

static char *convert(int *n)
{
    char    *str;
    size_t  size;
    int bias;

    bias = 1;
    if (*n < 0)
        bias++;
    size = _dig_count(*n) + bias;
    str = (char *)malloc(size); // check
    if (*n < 0)
    {
        str[0] = '-';
        *n *= -1;
    }
    str[size - 1] = '\0';
    return (str);
}

static char c_write(size_t n)
{
	return((n%10) + '0');
}

char *ft_itoa(int n)
{
    char    *str;
    int     len;
	int		i;

	str = convert(&n);
	len = ft_strlen(str) - 1;
	i = 0;
	while(len >= 0)
	{
		str[i] = c_write(n);
		n = n/10;
		i++;
		len--;
	}
	return(str);
}
