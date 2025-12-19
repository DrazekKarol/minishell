/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:56:50 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/05 09:22:14 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**get_args(t_token *tokens)
{
	size_t	count;
	char	**args;
	size_t	i;

	count = count_tokens(tokens, ARG) + 1;
	args = ft_calloc(count + 1, sizeof(char **));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (tokens->type == EXEC || tokens->type == ARG)
		{
			args[i] = ft_strdup(tokens->value);
			if (!args[i])
			{
				ft_free_tab(args);
				return (NULL);
			}
			i++;
		}
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}

char	**get_inputs(t_token *tokens)
{
	size_t	count;
	char	**inputs;
	size_t	i;

	count = count_tokens(tokens, REDIR_IN);
	inputs = ft_calloc(count + 1, sizeof(char **));
	if (!inputs)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (tokens->type == REDIR_IN)
		{
			inputs[i] = ft_strdup(tokens->value);
			if (!inputs[i])
				return (ft_free_tab(inputs), NULL);
			i++;
		}
		tokens = tokens->next;
	}
	inputs[i] = NULL;
	return (inputs);
}

char	**get_outputs(t_token *tokens)
{
	size_t	count;
	char	**outputs;
	size_t	i;

	count = count_tokens(tokens, REDIR_OUT)
		+ count_tokens(tokens, REDIR_APPEND);
	outputs = ft_calloc(count + 1, sizeof(char **));
	if (!outputs)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (tokens->type == REDIR_OUT || tokens->type == REDIR_APPEND)
		{
			outputs[i] = ft_strdup(tokens->value);
			if (!outputs[i])
				return (ft_free_tab(outputs), NULL);
			i++;
		}
		tokens = tokens->next;
	}
	outputs[i] = NULL;
	return (outputs);
}

char	**get_heredoc_limiters(t_token *tokens)
{
	size_t	count;
	char	**limiters;
	size_t	i;

	count = count_tokens(tokens, HEREDOC);
	limiters = ft_calloc(count + 1, sizeof(char **));
	if (!limiters)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (tokens->type == HEREDOC)
		{
			limiters[i] = ft_strdup(tokens->value);
			if (!limiters[i])
				return (ft_free_tab(limiters), NULL);
			i++;
		}
		tokens = tokens->next;
	}
	limiters[i] = NULL;
	return (limiters);
}

int	parse_tokens(t_data *data, t_exec *exec_list, t_token *tokens,
			int command_index)
{
	exec_list->type = determine_exec_type(tokens->value);
	exec_list->args = get_args(tokens);
	if (!exec_list->args)
		return (EXIT_FAILURE);
	exec_list->input = get_inputs(tokens);
	if (!exec_list->input)
		return (ft_free_tab(exec_list->args), EXIT_FAILURE);
	exec_list->output = get_outputs(tokens);
	if (!exec_list->output)
		return (ft_free_tab(exec_list->args),
			ft_free_tab(exec_list->input), EXIT_FAILURE);
	exec_list->heredoc_limiters = get_heredoc_limiters(tokens);
	if (!exec_list->heredoc_limiters)
		return (ft_free_tab(exec_list->args),
			ft_free_tab(exec_list->input),
			ft_free_tab(exec_list->output), EXIT_FAILURE);
	exec_list->append_mode = determine_append_mode(tokens);
	if (command_index > 0)
		exec_list->is_inpipe = 1;
	if (data->commands_count > command_index + 1)
		exec_list->is_outpipe = 1;
	return (EXIT_SUCCESS);
}
