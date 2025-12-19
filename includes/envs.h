/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:18:26 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/03 21:48:58 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVS_H
# define ENVS_H

# include "defines.h"
# include "libft.h"

t_env	*create_env_list(char **envp);
char	*ft_getenv(t_env *envs, char *name);
void	remove_env(t_env **envs, char *name);
void	add_env(t_env **envs, t_env *new_node);
t_env	*create_node(char *env);
void	clear_envs(t_env *envs);
char	**envs_to_char_tab(t_env *envs);
int		env_exists(const char *name, t_env *envs);
void	update_env(t_env *envs, char *name, char *value);

#endif