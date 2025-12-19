/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:19:56 by mstepnic          #+#    #+#             */
/*   Updated: 2024/12/09 13:42:28 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	int		len;

	len = 0;
	while (*s && ft_strchr(set, *s))
		s++;
	len = ft_strlen(s);
	while (s[len - 1] && ft_strchr(set, s[len - 1]))
		len--;
	return (ft_substr(s, 0, len));
}
