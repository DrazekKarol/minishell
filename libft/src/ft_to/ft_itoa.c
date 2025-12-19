/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:36:06 by mstepnic          #+#    #+#             */
/*   Updated: 2025/01/07 16:53:41 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		nbr_len;
	int		is_negative;
	char	*nbr;

	is_negative = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		is_negative = 1;
	nbr_len = ft_nbrlen(n, 10) + is_negative;
	nbr = (char *)malloc((nbr_len + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	nbr[nbr_len] = '\0';
	while (n != 0)
	{
		nbr[nbr_len - 1] = ft_abs(n % 10) + '0';
		n /= 10;
		nbr_len--;
	}
	if (is_negative)
		nbr[0] = '-';
	return (nbr);
}
