/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:41:49 by mstepnic          #+#    #+#             */
/*   Updated: 2024/12/11 15:57:36 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	int		difference;

	if (!dest && !src)
		return (NULL);
	difference = 1;
	i = 0;
	if (dest > src)
	{
		difference = -1;
		i = n - 1;
	}
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i += difference;
	}
	return (dest);
}
