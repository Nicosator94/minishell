/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:08:39 by niromano          #+#    #+#             */
/*   Updated: 2023/11/13 08:35:11 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_all(t_mini *minishell)
{
	t_cmd	*tmp;
	int		status;

	status = 0;
	tmp = minishell->cmd;
	while (tmp != NULL)
	{
		waitpid(tmp->pid, &status, 0);
		minishell->exit_status = WIFEXITED(status);
		if (minishell->exit_status == 1)
			minishell->exit_status = WEXITSTATUS(status);
		tmp = tmp->next;
	}
}
