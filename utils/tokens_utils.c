/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:53:30 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/12 16:45:23 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "defines.h"
#include "libft.h"

char	**token_list_to_char_tab(t_token *token_list)
{
	int		size;
	int		i;
	t_token	*temp;
	char	**tab;

	size = 0;
	temp = token_list;
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
		if (token_list->value)
			tab[i] = ft_strdup(token_list->value);
		i++;
		token_list = token_list->next;
	}
	return (tab);
}

t_token	*token_new(t_token_type type, char *value)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	return (new);
}

void	add_token_back(t_token **head, t_token *new)
{
	t_token	*temp;

	if (!head && !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

void	add_token_after(t_token *node, t_token *new_token)
{
	if (!node || !new_token)
		return ;
	new_token->next = node->next;
	new_token->prev = node;
	if (node->next)
		node->next->prev = new_token;
	node->next = new_token;
}

void	free_tokens(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}
