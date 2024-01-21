/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:40:22 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/21 19:47:21 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int a)
{
	return (a >= 32 && a <= 126);
}
/*int main()
{
	int a = 30;
	int check = ft_isprint(a);
	printf("%d", check);
}*/