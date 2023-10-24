/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:08:39 by niromano          #+#    #+#             */
/*   Updated: 2023/10/24 06:24:29 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_all(t_cmd *cmd, int *exit_status)
{
	t_cmd	*tmp;
	int		status;

	tmp = cmd;
	while (tmp != NULL)
	{
		waitpid(tmp->pid, &status, 0);
		*exit_status = WIFEXITED(status);
		if (*exit_status == 1)
			*exit_status = WEXITSTATUS(status);
		tmp = tmp->next;
	}
}
