/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 09:00:03 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/05 09:37:28 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	count_words(char const *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (!ft_isspace(*s) && (ft_isspace(*(s + 1)) || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

int	get_env_name_len(char *token_value, int is_in_quotes)
{
	int	len;

	len = 0;
	while (token_value[len] && !ft_isspace(token_value[len])
		&& token_value[len] != '\"' && token_value[len] != '$')
	{
		if (!is_in_quotes && (token_value[len] == '\''
				|| token_value[len] == '<' || token_value[len] == '>'
				|| token_value[len] == '|'))
			break ;
		len++;
	}
	return (len);
}

int	matches_pattern(char *filename, char **patterns)
{
	int	i;

	i = 0;
	while (patterns[i])
	{
		if (ft_strnstr(filename, patterns[i], ft_strlen(filename)) == NULL)
			return (EXIT_FAILURE);
		filename += ft_strlen(patterns[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	add_tokens_to_list(t_token *token, t_list *matched_files)
{
	t_token_type	original_type;
	t_list			*temp;
	t_token			*new_token;

	original_type = token->type;
	free(token->value);
	token->value = ft_strdup((char *)matched_files->content);
	if (!token->value)
		return (ft_lstclear(&matched_files, free), EXIT_FAILURE);
	temp = matched_files->next;
	while (temp)
	{
		new_token = create_token(ft_strdup((char *)temp->content),
				original_type);
		if (!new_token)
			return (ft_lstclear(&matched_files, free), EXIT_FAILURE);
		add_token_after(token, new_token);
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
