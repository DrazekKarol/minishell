/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:59:32 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/03 21:52:28 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envs.h"

char	*ft_getenv(t_env *envs, char *name)
{
	while (envs)
	{
		if (!ft_strncmp(name, envs->name, ft_strlen(name)))
			return (ft_strdup(envs->value));
		envs = envs->next;
	}
	return (NULL);
}

void	remove_env(t_env **envs, char *name)
{
	t_env	*temp;
	t_env	*prev;

	if (!ft_strncmp(name, (*envs)->name, ft_strlen(name)))
	{
		temp = *envs;
		*envs = (*envs)->next;
		free(temp->name);
		free(temp->value);
		free(temp);
		return ;
	}
	temp = *envs;
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(name)))
		{
			prev->next = temp->next;
			free(temp->name);
			free(temp->value);
			free(temp);
		}
		prev = temp;
		temp = temp->next;
	}
}

void	add_env(t_env **envs, t_env *new_node)
{
	t_env	*last;

	if (!new_node)
		return ;
	if (env_exists(new_node->name, *envs))
	{
		update_env(*envs, new_node->name, new_node->value);
		free(new_node->name);
		free(new_node->value);
		free(new_node);
		return ;
	}
	if (*envs)
	{
		last = *envs;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	else
		*envs = new_node;
}

t_env	*create_node(char *env)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_substr(env, 0, ft_strlen_to_char(env, '='));
	node->value = ft_strdup(ft_strchr(env, '=') + 1);
	node->next = NULL;
	return (node);
}

t_env	*create_env_list(char **envp)
{
	t_env	*envs;
	t_env	*new_node;
	int		i;

	envs = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_node(envp[i]);
		add_env(&envs, new_node);
		i++;
	}
	return (envs);
}
