/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:14:14 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/15 10:51:10 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "libft.h"

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

void	update_env(t_env *envs, char *name, char *new_value)
{
	while (envs)
	{
		if (!ft_strncmp(name, envs->name, ft_strlen(name)))
		{
			free(envs->value);
			envs->value = ft_strdup(new_value);
			return ;
		}
		envs = envs->next;
	}
}

void	free_envs(t_env *envs)
{
	t_env	*temp;

	while (envs)
	{
		temp = envs;
		envs = envs->next;
		if (temp->name)
			free(temp->name);
		if (temp->value)
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
	i = -1;
	while (++i < size)
	{
		tab[i] = ft_join_and_free(ft_strjoin(envs->name, "="), envs->value);
		if (!tab[i])
			return (ft_free_tab(tab), NULL);
		envs = envs->next;
	}
	return (tab);
}
