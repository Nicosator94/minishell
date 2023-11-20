/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:51:12 by niromano          #+#    #+#             */
/*   Updated: 2023/11/20 07:53:56 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	separate_cmd(t_cmd *cmd, t_mini *minishell)
{
	int		i;

	i = 0;
	while (cmd->line[i] == ' ' || (cmd->line[i] >= 9 && cmd->line[i] <= 13))
		i ++;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == '<' || cmd->line[i] == '>')
			i = get_file(cmd, i, minishell);
		else
			i = get_command(cmd, i, minishell);
		while ((cmd->line[i] == ' '
				|| (cmd->line[i] >= 9 && cmd->line[i] <= 13))
			&& cmd->line[i] != '\0')
			i ++;
	}
	free(cmd->line);
	cmd->line = NULL;
}

void	treatment_cmd(t_mini *minishell)
{
	t_cmd	*tmp;

	add_null_cmd(minishell->cmd);
	tmp = minishell->cmd;
	while (tmp != NULL)
	{
		separate_cmd(tmp, minishell);
		fill_mat_of_cmd(tmp, minishell);
		if (tmp->file != NULL)
			set_redi(tmp, minishell);
		tmp = tmp->next;
	}
	create_here_doc(minishell);
}
