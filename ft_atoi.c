/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:39:28 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/31 17:20:53 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	_ft_is_space(char c)
{
	return (c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r' || c == ' ');
}

static	int	_ft_to_digit(char c)
{
	return (c - '0');
}

// 9223372036854775807

int	ft_atoi(const char *str)
{
	long long	res;
	int			sign;

	while (_ft_is_space(*str))
		str++;
	sign = 1;
	res = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = ((res * 10) + _ft_to_digit(*str));
		str++;
	}
	return (sign * res);
}