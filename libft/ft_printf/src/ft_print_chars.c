/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:26:09 by mstepnic          #+#    #+#             */
/*   Updated: 2024/12/26 17:44:00 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(t_format *flags, int c)
{
	char	*formatted_str;

	if (flags->width <= 1 || c == '%')
	{
		ft_putchar_fd(c, 1);
		return (1);
	}
	else
		formatted_str = ft_calloc(flags->width + 1, sizeof(char));
	if (!formatted_str)
		return (0);
	ft_memset(formatted_str, ' ', flags->width);
	if (!c && flags->width > 1)
	{
		ft_putchar_fd(0, 1);
		ft_putstr_fd(formatted_str + 1, 1);
		free(formatted_str);
		return ((int)flags->width);
	}
	if (flags->minus)
		formatted_str[0] = c;
	else
		formatted_str[flags->width - 1] = c;
	return (print_and_free(formatted_str));
}

int	print_str(t_format *flags, char *str)
{
	size_t	strlen;
	char	*temp;
	char	*formatted_str;

	if (!str)
		temp = ft_strdup("(null)");
	else if (flags->precision >= 0)
		temp = ft_substr(str, 0, flags->precision);
	else
		temp = ft_strdup(str);
	if (!temp)
		return (0);
	strlen = ft_strlen(temp);
	if (strlen >= flags->width)
		return (print_and_free(temp));
	formatted_str = ft_calloc(flags->width + 1, sizeof(char));
	if (!formatted_str)
		return (0);
	ft_memset(formatted_str, ' ', flags->width);
	if (flags->minus == 1)
		ft_memcpy(formatted_str, temp, strlen);
	else
		ft_memcpy((formatted_str + (flags->width - strlen)), temp, strlen);
	free(temp);
	return (print_and_free(formatted_str));
}
