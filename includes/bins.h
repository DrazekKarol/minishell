/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bins.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:41:00 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/13 17:51:16 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINS_H
# define BINS_H

# include "defines.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define PATH_SIZE 4096

int	ft_echo(t_exec *exec);
int	ft_cd(t_data *data, t_exec *exec);
int	ft_pwd(t_data *data);
int	ft_export(t_data *data, t_exec *exec);
int	ft_unset(t_data *data, t_exec *exec);
int	ft_env(t_data *data, t_exec *exec);
int	ft_exit(t_data *data, t_exec *exec);

#endif