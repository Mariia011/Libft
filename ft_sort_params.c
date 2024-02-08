/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:59:08 by marikhac          #+#    #+#             */
/*   Updated: 2024/01/19 15:01:59 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);
/*{
	write(1, &c, 1);
}*/

int	ft_strcmp(char *s1, char *s2)
{
	int	res;

	if (s1 == 0 || s2 == 0)
		return (0);
	while (*s1)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	res = ((const unsigned char)(*s1) - (const unsigned char)(*s2));
	if (res < 0)
		return (-1);
	if (res > 0)
		return (1);
	return (0);
}

void	ft_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

int	partition(char **arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = high;
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (ft_strcmp(arr[j], arr[pivot]) < 0)
			ft_swap(&arr[++i], &arr[j]);
		++j;
	}
	ft_swap(&arr[++i], &arr[high]);
	return (i);
}

void	_qsort(char **arr, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = partition(arr, low, high);
		_qsort(arr, pivot + 1, high);
		_qsort(arr, low, pivot - 1);
	}
}

int	main(int ac, char **av)
{
	int	index;
	int	jindex;

	if (ac > 2)
	{
		_qsort(av + 1, 0, ac - 2);
	}
	index = 1;
	while (index < ac)
	{
		jindex = 0;
		while (av[index][jindex])
		{
			ft_putchar(av[index][jindex++]);
		}
		ft_putchar('\n');
		index++;
	}
	return (0);
}
