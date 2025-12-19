/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:40:12 by mstepnic          #+#    #+#             */
/*   Updated: 2024/12/27 19:41:22 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*join_width(int left, int width, char *w_str, char *f_str)
{
	char	*temp_str;

	temp_str = NULL;
	if (width > 0 && left)
		temp_str = ft_join_and_free(f_str, w_str);
	else if (width > 0 && !left)
		temp_str = ft_join_and_free(w_str, f_str);
	return (temp_str);
}

int	print_int(t_format *flags, int nbr)
{
	char	*f_str;
	char	*nbrstr;
	char	*w_str;
	int		width;

	if (flags->plus || nbr < 0)
		flags->space = 0;
	nbrstr = ft_itoa_base(nbr, "0123456789");
	f_str = get_flags_str(flags, (nbr < 0), nbrstr);
	f_str = ft_join_and_free(f_str, nbrstr);
	if (flags->width > ft_strlen(f_str))
	{
		width = flags->width - ft_strlen(f_str);
		w_str = ft_calloc(width + 1, sizeof(char));
		if (!w_str)
			return (0);
		ft_memset(w_str, ' ', width);
		f_str = join_width(flags->minus, width, w_str, f_str);
	}
	return (print_and_free(f_str));
}

int	print_uint(t_format *flags, unsigned int nbr)
{
	char	*f_str;
	char	*nbrstr;
	char	*w_str;
	int		width;

	flags->plus = 0;
	flags->space = 0;
	nbrstr = ft_uitoa_base(nbr, "0123456789");
	f_str = get_flags_str(flags, 0, nbrstr);
	f_str = ft_join_and_free(f_str, nbrstr);
	width = flags->width - ft_strlen(f_str);
	if (flags->width > ft_strlen(f_str))
	{
		width = flags->width - ft_strlen(f_str);
		w_str = ft_calloc(width + 1, sizeof(char));
		if (!w_str)
			return (0);
		ft_memset(w_str, ' ', width);
		f_str = join_width(flags->minus, width, w_str, f_str);
	}
	return (print_and_free(f_str));
}

int	print_hex(t_format *flags, unsigned int nbr)
{
	char	*f_str;
	char	*nbrstr;
	char	*w_str;
	int		width;

	nbrstr = ft_uitoa_base(nbr, "0123456789abcdef");
	f_str = get_flags_str(flags, 0, nbrstr);
	f_str = ft_join_and_free(f_str, nbrstr);
	if (flags->spc == 'X')
		hex_toupper(f_str);
	width = flags->width - ft_strlen(f_str);
	if (width > 0)
		w_str = ft_calloc(width + 1, sizeof(char));
	if (width > 0)
	{
		ft_memset(w_str, ' ', width);
		f_str = join_width(flags->minus, width, w_str, f_str);
	}
	return (print_and_free(f_str));
}

int	print_ptr(t_format *flags, void *ptr)
{
	char	*f_str;
	char	*hex;
	char	*width;
	size_t	w_len;

	if (!ptr)
		f_str = ft_strdup("(nil)");
	else
	{
		hex = ft_ulltoa_base((unsigned long)ptr, "0123456789abcdef");
		f_str = ft_strjoin("0x", hex);
		free(hex);
	}
	if (flags->width > ft_strlen(f_str))
	{
		w_len = flags->width - ft_strlen(f_str);
		width = ft_calloc(w_len + 1, sizeof(char));
		ft_memset(width, ' ', w_len);
		if (flags->minus)
			f_str = ft_join_and_free(f_str, width);
		else
			f_str = ft_join_and_free(width, f_str);
	}
	return (print_and_free(f_str));
}
