/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:15:05 by mstepnic          #+#    #+#             */
/*   Updated: 2024/12/30 14:08:38 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct s_format
{
	size_t	percent;
	size_t	minus;
	size_t	plus;
	size_t	space;
	size_t	hsh;
	size_t	width;
	int		precision;
	size_t	zeros;
	int		spc;
}			t_format;

int			ft_printf(const char *format, ...);
int			get_flags(t_format *flags, char *format);
int			get_specifier(int c);
int			get_flag(int c);
int			print_char(t_format *flags, int c);
int			print_str(t_format *flags, char *str);
int			print_int(t_format *flags, int nbr);
int			print_uint(t_format *flags, unsigned int nbr);
int			print_hex(t_format *flags, unsigned int nbr);
int			print_ptr(t_format *flags, void *ptr);
int			print_and_free(char *str);

void		reset_flags(t_format *flags);
void		hex_toupper(char *hex);

char		*ft_ltoa_base(long nbr, char *base);
char		*ft_ulltoa_base(unsigned long long nbr, char *base);
char		*get_flags_str(t_format *flags, int is_negative, char *nbrstr);

size_t		read_width(t_format *flags, char *format);
size_t		read_precision(t_format *flags, char *format);
size_t		read_zeros(t_format *flags, char *format);

#endif