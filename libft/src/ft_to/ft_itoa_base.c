/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:57:32 by mstepnic          #+#    #+#             */
/*   Updated: 2024/12/24 21:18:17 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int nbr, char *base)
{
	int		base_len;
	size_t	nbr_len;
	char	*nbrstr;
	int		i;

	base_len = (int)ft_strlen(base);
	nbr_len = ft_nbrlen(nbr, base_len);
	nbrstr = ft_calloc(nbr_len + 1, sizeof(char));
	if (!nbrstr)
		return (NULL);
	i = nbr_len - 1;
	while (i >= 0)
	{
		nbrstr[i] = base[ft_abs(nbr % base_len)];
		nbr /= base_len;
		i--;
	}
	return (nbrstr);
}
