/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstepnic <mstepnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:44:44 by mstepnic          #+#    #+#             */
/*   Updated: 2025/10/13 19:37:00 by mstepnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "libft.h"

void	free_exec(t_exec *exec)
{
	if (exec->args)
		ft_free_tab(exec->args);
	if (exec->redirs)
		free_tokens(exec->redirs);
	free(exec);
}
