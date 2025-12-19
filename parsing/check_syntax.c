/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:01:41 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/03 16:32:02 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*getredir(char *input)
{
	if (*input == '\0')
		return (ft_strdup("newline"));
	else if (*input == '>' && *(input + 1) == '>')
		return (ft_strdup(">>"));
	else if (*input == '>' && *(input + 1) != '>')
		return (ft_strdup(">"));
	else if (*input == '<' && *(input + 1) == '<')
		return (ft_strdup("<<"));
	else if (*input == '<' && *(input + 1) != '<')
		return (ft_strdup("<"));
	else
		return (NULL);
}

int	check_token(char *input)
{
	int		i;
	char	*redir;

	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	if (input[i] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	redir = getredir(&input[i]);
	if (redir)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(redir, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		free(redir);
		return (EXIT_FAILURE);
	}
	i++;
	return (EXIT_SUCCESS);
}

int	check_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	if (input[i] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (input[i] == '\0')
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check(int singleq, int doubleq, char *input, char *redir)
{
	int	i;

	i = 0;
	if (!singleq && !doubleq)
	{
		if (input[i] == '|' && check_pipe(&input[i + 1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (input[i] == '>' || input[i] == '<')
			redir = getredir(&input[i]);
		if (redir)
		{
			i += ft_strlen(redir);
			if (check_token(&input[i]))
				return (free(redir), EXIT_FAILURE);
			free(redir);
		}
	}
	return (EXIT_SUCCESS);
}

int	check_for_unexpected_token(char *input)
{
	int		singleq;
	int		doubleq;
	char	*redir;

	singleq = 0;
	doubleq = 0;
	if (*input == '|')
		return (ft_putstr_fd("syntax error near unexpected token `|'\n",
				STDERR_FILENO), EXIT_FAILURE);
	while (*input)
	{
		redir = NULL;
		while (*input && ft_isspace(*input))
			input++;
		if (!*input)
			break ;
		if (*input == '\'' && !doubleq)
			singleq = !singleq;
		else if (*input == '"' && !singleq)
			doubleq = !doubleq;
		if (check(singleq, doubleq, input, redir) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		input++;
	}
	return (EXIT_SUCCESS);
}
