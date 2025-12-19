/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:19:26 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/03 23:12:36 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_exec_type	determine_exec_type(char *cmd)
{
	if (ft_strncmp(cmd, BUILTIN_CD, ft_strlen(BUILTIN_CD) + 1) == 0
		|| ft_strncmp(cmd, BUILTIN_ECHO, ft_strlen(BUILTIN_ECHO) + 1) == 0
		|| ft_strncmp(cmd, BUILTIN_ENV, ft_strlen(BUILTIN_ENV) + 1) == 0
		|| ft_strncmp(cmd, BUILTIN_EXIT, ft_strlen(BUILTIN_EXIT) + 1) == 0
		|| ft_strncmp(cmd, BUILTIN_EXPORT, ft_strlen(BUILTIN_EXPORT) + 1) == 0
		|| ft_strncmp(cmd, BUILTIN_PWD, ft_strlen(BUILTIN_PWD) + 1) == 0
		|| ft_strncmp(cmd, BUILTIN_UNSET, ft_strlen(BUILTIN_UNSET) + 1) == 0)
		return (BUILTIN);
	return (BINARY);
}

int	determine_append_mode(t_token *tokens)
{
	while (tokens)
		tokens = tokens->next;
	while (tokens)
	{
		if (tokens->type == REDIR_APPEND)
			return (1);
		if (tokens->type == REDIR_OUT)
			return (0);
		tokens = tokens->prev;
	}
	return (0);
}

void	free_exec_list(t_exec *head)
{
	t_exec	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->args)
			ft_free_tab(temp->args);
		if (temp->input)
			ft_free_tab(temp->input);
		if (temp->output)
			ft_free_tab(temp->output);
		if (temp->heredoc_limiters)
			ft_free_tab(temp->heredoc_limiters);
		free(temp);
	}
}

t_exec	*create_exec_list(int nb_of_commands)
{
	t_exec	*head;
	t_exec	*temp;
	t_exec	*new;

	head = ft_calloc(1, sizeof(t_exec));
	if (!head)
		return (NULL);
	temp = head;
	while (nb_of_commands-- > 1)
	{
		new = ft_calloc(1, sizeof(t_exec));
		if (!new)
		{
			free_exec_list(head);
			return (NULL);
		}
		temp->next = new;
		temp = temp->next;
	}
	return (head);
}
