/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:35:56 by mstepnic          #+#    #+#             */
/*   Updated: 2026/01/20 21:37:13 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "defines.h"
# include "libft.h"

// signals/signals.c
void	set_up_signals_for_parent(void);

// lexer/lexer.c
t_token	*lexer(t_data *data);

// parser/parser.c
t_ast	*parser(t_data *data);

// execution/execute.c
void	execute(t_data *data);

#endif