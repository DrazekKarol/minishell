/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bins.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2025/12/18 17:18:21 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINS_H
# define BINS_H

# include "defines.h"
# include "libft.h"
# include <stdio.h>
# include "envs.h"
# include <stdlib.h>
# include <string.h>

# define PATH_SIZE 4096

int		ft_echo(t_exec *exec);
int		ft_cd(t_data *data, t_exec *exec);
int		ft_pwd(t_data *data);
int		ft_export(t_data *data, t_exec *exec);
int		ft_unset(t_data *data, t_exec *exec);
int		ft_env(t_data *data, t_exec *exec);
int		ft_exit(t_data *data, t_exec *exec);
void	free_exec_list_local(t_exec *head);

#endif
