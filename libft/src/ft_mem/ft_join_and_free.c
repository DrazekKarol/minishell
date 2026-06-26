/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:26:48 by mstepnic          #+#    #+#             */
/*   Updated: 2025/01/07 17:02:54 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join_and_free(char *str1, char *str2)
{
	char	*temp;

	if (!str1 && !str2)
		return (NULL);
	if (!str1)
		return (str2);
	if (!str2)
		return (str1);
	temp = ft_strjoin(str1, str2);
	if (!temp)
		return (NULL);
	free(str1);
	return (temp);
}
