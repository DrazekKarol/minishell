/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:51:16 by mstepnic          #+#    #+#             */
/*   Updated: 2026/01/13 14:52:33 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		&& (token->prev && (token->prev->type == TK_REDIR_IN
				|| token->prev->type == TK_REDIR_OUT
				|| token->prev->type == TK_REDIR_APPEND)))
		return (ft_lstclear(&matched_files, free),
			printf("*: ambiguous redirect\n"), EXIT_FAILURE);
	if (add_tokens_to_list(token, matched_files) == EXIT_FAILURE)
		return (ft_lstclear(&matched_files, free), EXIT_FAILURE);
	while (token->prev)
		token = token->prev;
	return (ft_lstclear(&matched_files, free), EXIT_SUCCESS);
}

bool	is_in_qoutes(char *input)
{
	int	is_in_qoutes;
	int	i;

	is_in_qoutes = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			is_in_qoutes = input[i++];
		if (input[i] == is_in_qoutes)
			is_in_qoutes = 0;
		if (input[i] == '*' && !is_in_qoutes)
			return (false);
		if (input[i])
			i++;
	}
	return (true);
}

int	handle_wildcards(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp && temp->type != TK_EOF)
	{
		if ((temp->prev && temp->prev->type == TK_REDIR_HEREDOC)
			|| (temp->value && is_in_qoutes(temp->value)))
			;
		else if (temp->value && ft_strchr(temp->value, '*'))
		{
			if (extend_wildcard(temp) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
