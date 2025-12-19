/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:26:53 by mstepnic          #+#    #+#             */
/*   Updated: 2025/11/26 18:24:52 by kdrazek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envs.h"

int	env_exists(const char *name, t_env *envs)
{
	while (envs)
	{
		if (!ft_strncmp(name, envs->name, ft_strlen(name)))
			return (1);
		envs = envs->next;
	}
	return (0);
}

void	update_env(t_env *envs, char *name, char *value)
{
	while (envs)
	{
		if (!ft_strncmp(name, envs->name, ft_strlen(name)))
		{
			free(envs->value);
			envs->value = ft_strdup(value);
			return ;
		}
		envs = envs->next;
	}
}

void	clear_envs(t_env *envs)
{
	t_env	*temp;

	while (envs)
	{
		temp = envs;
		envs = envs->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

char	**envs_to_char_tab(t_env *envs)
{
	int		size;
	int		i;
	t_env	*temp;
	char	**tab;

	size = 0;
	temp = envs;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	tab = ft_calloc(size + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	tab[size] = NULL;
	i = 0;
	while (i < size)
	{
		tab[i] = ft_join_and_free(ft_strjoin(envs->name, "="), envs->value);
		i++;
	}
	return (tab);
}
