/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unbrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:17:09 by mstepnic          #+#    #+#             */
/*   Updated: 2024/12/24 21:21:03 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_unbrlen(unsigned long long nbr, int base)
{
	size_t	nbr_len;

	if (!nbr)
		return (1);
	nbr_len = 0;
	while (nbr)
	{
		nbr /= base;
		nbr_len++;
	}
	return (nbr_len);
}
