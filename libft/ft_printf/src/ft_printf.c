/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:13:22 by mstepnic          #+#    #+#             */
/*   Updated: 2025/01/07 16:17:46 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print(va_list ap, t_format *flags, char *format, int *length)
{
	int	flags_len;

	flags_len = get_flags(flags, (char *)(format + 1));
	if (flags->spc == 'c')
		*length += print_char(flags, va_arg(ap, int));
	else if (flags->spc == 's')
		*length += print_str(flags, va_arg(ap, char *));
	else if (flags->spc == 'd' || flags->spc == 'i')
		*length += print_int(flags, va_arg(ap, int));
	else if (flags->spc == 'x' || flags->spc == 'X')
		*length += print_hex(flags, va_arg(ap, unsigned int));
	else if (flags->spc == 'u')
		*length += print_uint(flags, va_arg(ap, unsigned int));
	else if (flags->spc == 'p')
		*length += print_ptr(flags, va_arg(ap, void *));
	else
		*length += ft_putchar_fd('%', 1);
	return (flags_len + 1);
}

int	ft_printf(const char *format, ...)
{
	int			length;
	va_list		ap;
	t_format	*flags;

	length = 0;
	flags = ft_calloc(1, sizeof(t_format));
	va_start(ap, format);
	while (*format)
	{
		reset_flags(flags);
		if (*(char *)format == '%')
			format += print(ap, flags, (char *)format, &length);
		else
		{
			length += ft_putchar_fd(*(char *)format, 1);
			format++;
		}
	}
	va_end(ap);
	free(flags);
	return (length);
}
