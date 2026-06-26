/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbrs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 14:11:48 by mstepnic          #+#    #+#             */
/*   Updated: 2024/12/26 16:59:15 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	hex_toupper(char *hex)
{
	while (*hex)
	{
		if (ft_isalpha(*hex))
			*hex = ft_toupper(*hex);
		hex++;
	}
}

size_t	get_str_len(t_format *flags, size_t nbrstr_len, int is_negative)
{
	size_t	len;

	len = 0;
	if (flags->spc == 'd' || flags->spc == 'i')
		len += flags->space + (flags->space || is_negative);
	else if (flags->hsh && (flags->spc == 'x' || flags->spc == 'X'))
		len += 2;
	if (flags->precision > 0 && (flags->precision > (int)nbrstr_len))
		len += flags->precision - nbrstr_len;
	else if (flags->zeros > nbrstr_len && flags->precision == -1)
		len += flags->zeros - nbrstr_len;
	return (len + 1);
}

char	*get_flags_str(t_format *flags, int is_neg, char *nstr)
{
	size_t	nstr_len;
	char	*flags_str;
	int		i;

	nstr_len = ft_strlen(nstr);
	flags_str = ft_calloc(get_str_len(flags, nstr_len, is_neg) + 1, 1);
	if (!flags_str)
		return (NULL);
	i = 0;
	if (flags->hsh && *nstr != '0' && (flags->spc == 'x' || flags->spc == 'X'))
	{
		flags_str[i++] = '0';
		flags_str[i++] = 'x';
	}
	if (is_neg)
		flags_str[i++] = '-';
	else if (flags->plus && !is_neg)
		flags_str[i++] = '+';
	else if (flags->space)
		flags_str[i++] = ' ';
	if ((flags->zeros > nstr_len) && flags->precision == -1)
		ft_memset(flags_str + i, '0', flags->zeros - nstr_len - is_neg);
	else if (flags->precision > 0 && (flags->precision > (int)nstr_len))
		ft_memset(flags_str + i, '0', flags->precision - nstr_len);
	return (flags_str);
}
