/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:51:16 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/05 09:38:27 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*match_files(t_list *files, char *token_value)
{
	t_list	*matched_files;
	t_list	*new_file;
	char	**patterns;

	patterns = ft_split(token_value, '*');
	if (!patterns)
		return (NULL);
	matched_files = NULL;
	while (files)
	{
		if (matches_pattern((char *)files->content, patterns) == EXIT_SUCCESS)
		{
			new_file = ft_lstnew(ft_strdup((char *)files->content));
			if (!new_file)
			{
				ft_free_tab(patterns);
				ft_lstclear(&matched_files, free);
				return (NULL);
			}
			ft_lstadd_back(&matched_files, new_file);
		}
		files = files->next;
	}
	return (ft_free_tab(patterns), matched_files);
}

t_list	*get_all_files(void)
{
	t_list			*files;
	t_list			*new_file;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	files = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_REG
			|| (entry->d_type == DT_DIR && entry->d_name[0] != '.'))
		{
			new_file = ft_lstnew(ft_strdup(entry->d_name));
			if (!new_file)
				return (closedir(dir), ft_lstclear(&files, free), NULL);
			ft_lstadd_back(&files, new_file);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (files);
}

int	extend_wildcard(t_token *token)
{
	t_list		*all_files;
	t_list		*matched_files;

	all_files = get_all_files();
	if (!all_files)
		return (EXIT_FAILURE);
	matched_files = match_files(all_files, token->value);
	ft_lstclear(&all_files, free);
	if (!matched_files)
		return (EXIT_FAILURE);
	if (ft_lstsize(matched_files) == 0)
		return (ft_lstclear(&matched_files, free), EXIT_SUCCESS);
	if (ft_lstsize(matched_files) > 1
		&& (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == REDIR_APPEND))
		return (ft_lstclear(&matched_files, free),
			printf("*: ambiguous redirect\n"), EXIT_FAILURE);
	if (add_tokens_to_list(token, matched_files) == EXIT_FAILURE)
		return (ft_lstclear(&matched_files, free), EXIT_FAILURE);
	while (token->prev)
		token = token->prev;
	return (ft_lstclear(&matched_files, free), EXIT_SUCCESS);
}

int	handle_wildcards(t_token *tokens)
{
	while (tokens)
	{
		if (ft_strchr(tokens->value, '*'))
		{
			if (tokens->type != HEREDOC
				&& extend_wildcard(tokens) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		tokens = tokens->next;
	}
	return (EXIT_SUCCESS);
}
