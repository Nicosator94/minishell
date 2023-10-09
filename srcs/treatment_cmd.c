/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:51:12 by niromano          #+#    #+#             */
/*   Updated: 2023/10/09 08:03:44 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	separate_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->line[i] == ' ' || (cmd->line[i] >= 9 && cmd->line[i] <= 13))
		i ++;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == '<' || cmd->line[i] == '>')
			i = get_file(cmd, i);
		else
			i = get_command(cmd, i);
		while ((cmd->line[i] == ' ' || (cmd->line[i] >= 9 && cmd->line[i] <= 13)) && cmd->line[i] != '\0')
			i ++;
	}
	free(cmd->line);
}

// void	fill_mat_of_cmd(t_cmd *cmd)
// {
	
// }

void	treatment_cmd(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		cmd->file = NULL;
		cmd->l_cmd = NULL;
		separate_cmd(cmd);
		// fill_mat_of_cmd(cmd);
		cmd = cmd->next;
	}
}
