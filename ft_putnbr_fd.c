/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:37:13 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/06 19:08:41 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", fd);
		n = -n;
	}
	if (n < 10)
	{
		ft_putchar_fd((n % 10) + '0', fd);
		return ;
	}
	ft_putnbr_fd((n / 10), fd);
	ft_putnbr_fd((n % 10), fd);
}
