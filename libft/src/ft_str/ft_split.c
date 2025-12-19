/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:32:47 by mstepnic          #+#    #+#             */
/*   Updated: 2024/12/11 20:31:36 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_str_count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static size_t	get_str_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static void	*free_array(char **arr_to_free, int n)
{
	while (n >= 0)
	{
		free(arr_to_free[n]);
		n--;
	}
	free(arr_to_free);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**splited_str;
	size_t	str_count;
	size_t	str_size;
	int		i;

	str_count = get_str_count(s, c) + 1;
	splited_str = (char **)malloc(str_count * sizeof(s));
	if (!splited_str)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			str_size = get_str_len(s, c) + 1;
			splited_str[i] = (char *)malloc(str_size * sizeof(char));
			if (!splited_str[i])
				return (free_array(splited_str, i));
			ft_strlcpy(splited_str[i++], s, str_size);
			s += str_size - 2;
		}
		s++;
	}
	splited_str[i] = NULL;
	return (splited_str);
}
