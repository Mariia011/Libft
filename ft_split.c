/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:34:09 by marikhac          #+#    #+#             */
/*   Updated: 2024/02/08 13:28:34 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char const c)
{
	int	word;
	int	flag;

	word = 0;
	flag = 0;
	while (*str)
	{
		if (*str != c)
			flag = 1;
		else if (*str == c && flag)
		{
			word++;
			flag = 0;
		}
		str++;
	}
	return (word + flag);
}

static int	current_word_len(char const **s, char c)
{
	int	count;

	count = 0;
	while (**s && **s != c)
	{
		count++;
		(*s)++;
	}
	return (count);
}

static void	*dealloc(char **str, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(str[i]);
		i++;
	}
	return (NULL);
}

static char	**__split(char const *s, char c, char **arr, int size)
{
	int			i;
	char const	*tmp;
	int			current_len;

	i = 0;
	while (i < size)
	{
		while (*s && *s == c)
			s++;
		tmp = s;
		current_len = current_word_len(&s, c);
		arr[i] = malloc(current_len + 1);
		if (!arr[i])
			return (dealloc(arr, i));
		ft_strlcpy(arr[i], tmp, current_len + 1);
		i++;
	}
	arr[size] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		size;

	if (!s)
		return (NULL);
	size = count_words(s, c);
	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (__split(s, c, arr, size));
}

// int main(void) {
//     char const *str = "Hello,world,this,is,an,example";
//     char delimiter = ',';

//     char **result = ft_split(str, delimiter);

//     if (result == NULL) {
//         printf("Splitting failed.\n");
//         return 1;
//     }

//     for (int i = 0; result[i] != NULL; i++) {
//         printf("%s\n", result[i]);
//         free(result[i]);
//     }
//     free(result);

//     return 0;
// }
