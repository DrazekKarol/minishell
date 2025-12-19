/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:27:46 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/05 09:42:23 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	replace_value(char **token_value, char **env_value, int len, int i)
{
	char	*new_token_value;
	char	*temp;

	if (!(*env_value))
		*env_value = ft_strdup("");
	if (!(*env_value))
		return (EXIT_FAILURE);
	new_token_value = ft_substr(*token_value, 0, i);
	if (!new_token_value)
		return (EXIT_FAILURE);
	temp = ft_substr(*token_value, i + len + 1,
			ft_strlen(*token_value) - (i + len + 1));
	if (!temp)
		return (free(new_token_value), EXIT_FAILURE);
	new_token_value = ft_join_and_free(new_token_value, *env_value);
	if (!new_token_value)
		return (free(temp), EXIT_FAILURE);
	new_token_value = ft_join_and_free(new_token_value, temp);
	free(temp);
	if (!new_token_value)
		return (EXIT_FAILURE);
	free(*token_value);
	*token_value = new_token_value;
	return (EXIT_SUCCESS);
}

int	handle_exit_status(t_data *data, char **token_value, int *i)
{
	char	*env_value;
	int		len;

	env_value = ft_itoa(data->exit_status);
	if (!env_value)
		return (EXIT_FAILURE);
	if (replace_value(token_value, &env_value, 1, *i) == EXIT_FAILURE)
		return (free(env_value), EXIT_FAILURE);
	len = ft_strlen(env_value) - 1;
	*i += len;
	free(env_value);
	return (EXIT_SUCCESS);
}

int	extend_env(t_data *data, char **token_value, int is_in_quotes, int *i)
{
	int		len;
	char	*env_name;
	char	*env_value;

	if ((*token_value)[*i + 1] == '?')
		return (handle_exit_status(data, token_value, i));
	len = get_env_name_len(&(*token_value)[*i + 1], is_in_quotes);
	env_name = ft_substr(*token_value, *i + 1, len);
	if (!env_name)
		return (EXIT_FAILURE);
	env_value = ft_getenv(data->envs, env_name);
	if (count_words(env_value) > 1 && !is_in_quotes)
		return (free(env_value), printf("$%s: ambiguous redirect\n", env_name),
			free(env_name), EXIT_FAILURE);
	free(env_name);
	if (replace_value(token_value, &env_value, len, *i) == EXIT_FAILURE)
		return (free(env_value), EXIT_FAILURE);
	len = ft_strlen(env_value) - 1;
	free(env_value);
	return (*i += len, EXIT_SUCCESS);
}

int	find_env(t_data *data, t_token *tokens)
{
	int	i;
	int	is_in_quotes;

	i = 0;
	is_in_quotes = 0;
	while (tokens->value[i])
	{
		if (tokens->value[i] == '\'')
		{
			i++;
			while (tokens->value[i] && tokens->value[i] != '\'')
				i++;
		}
		if (tokens->value[i] == '\"')
			is_in_quotes = !is_in_quotes;
		else if (tokens->value[i] == '$')
		{
			if (extend_env(data, &tokens->value, is_in_quotes, &i))
				return (EXIT_FAILURE);
			if (!ft_strchr(tokens->value, '$'))
				break ;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	handle_envs(t_data *data, t_token *tokens)
{
	while (tokens)
	{
		if (ft_strchr(tokens->value, '$'))
		{
			if (find_env(data, tokens) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
