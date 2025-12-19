/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 18:45:18 by mstepnic          #+#    #+#             */
/*   Updated: 2024/12/24 18:46:47 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ultoa_base(unsigned long nbr, char *base)
{
	int		base_len;
	size_t	nbr_len;
	char	*nbrstr;
	int		i;

	base_len = (int)ft_strlen(base);
	nbr_len = ft_unbrlen(nbr, base_len);
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
