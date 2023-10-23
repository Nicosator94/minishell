/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:08:39 by niromano          #+#    #+#             */
/*   Updated: 2023/10/23 11:20:09 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_all(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		status_value;

	tmp = cmd;
	status_value = 0;
	while (tmp != NULL)
	{
		waitpid(tmp->pid, &status_value, 0);
		tmp = tmp->next;
	}
}
