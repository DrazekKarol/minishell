/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 19:27:47 by mstepnic          #+#    #+#             */
/*   Updated: 2024/12/10 16:33:29 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	to_find_len;
	size_t	i;

	if (!*to_find || (!str && n == 0))
		return ((char *)str);
	to_find_len = ft_strlen(to_find);
	i = 0;
	while (str[i] && i < n && (to_find_len + i - 1) < n)
	{
		if (!ft_strncmp((str + i), to_find, to_find_len))
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
