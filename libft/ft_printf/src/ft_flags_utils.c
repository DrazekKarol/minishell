/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:49:35 by mstepnic          #+#    #+#             */
/*   Updated: 2025/01/07 16:01:52 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reset_flags(t_format *flags)
{
	flags->hsh = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->precision = -1;
	flags->spc = 0;
	flags->width = 0;
	flags->zeros = 0;
}

size_t	read_width(t_format *flags, char *format)
{
	int		bytes_read;

	bytes_read = 0;
	while (ft_isdigit(*format))
	{
		flags->width = (flags->width * 10) + (*format - '0');
		bytes_read++;
		format++;
	}
	return (bytes_read);
}

size_t	read_precision(t_format *flags, char *format)
{
	int		bytes_read;

	bytes_read = 0;
	flags->precision = 0;
	if (flags->zeros > flags->width)
	{
		flags->width = flags->zeros;
		flags->zeros = 0;
	}
	while (ft_isdigit(*format))
	{
		flags->precision = (flags->precision * 10) + (*format - '0');
		bytes_read++;
		format++;
	}
	return (bytes_read);
}

size_t	read_zeros(t_format *flags, char *format)
{
	int		bytes_read;

	bytes_read = 0;
	while (ft_isdigit(*format))
	{
		flags->zeros = (flags->zeros * 10) + (*format - '0');
		bytes_read++;
		format++;
	}
	return (bytes_read);
}
