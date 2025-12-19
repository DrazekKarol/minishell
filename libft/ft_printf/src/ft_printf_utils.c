/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:51:38 by mstepnic          #+#    #+#             */
/*   Updated: 2025/01/07 16:00:50 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_and_free(char *str)
{
	size_t	length;

	length = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (length);
}

int	get_flags(t_format *flags, char *format)
{
	int	i;

	i = 0;
	while (format[i] && !ft_isalpha(format[i]) && format[i] != '%')
	{
		if (format[i] == '-')
			flags->minus = 1;
		else if (format[i] == '+')
			flags->plus = 1;
		else if (format[i] == ' ')
			flags->space = 1;
		else if (format[i] == '#')
			flags->hsh = 1;
		else if (format[i] >= '1' && format[i] <= '9')
			i += read_width(flags, (format + i)) - 1;
		else if (format[i] == '.')
			i += read_precision(flags, (format + i) + 1);
		else if (format[i] == '0')
			i += read_zeros(flags, (format + i) + 1);
		else
			break ;
		i++;
	}
	flags->spc = format[i];
	return (i + 1);
}
