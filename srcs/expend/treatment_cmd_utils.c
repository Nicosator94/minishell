/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 08:45:04 by niromano          #+#    #+#             */
/*   Updated: 2023/10/25 06:52:31 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_mat_of_cmd(t_cmd *cmd, t_mini *minishell)
{
	int		i;
	t_list	*tmp;

	i = 0;
	cmd->cmd = malloc(sizeof(char *) * (ft_lstsize(cmd->l_cmd) + 1));
	if (cmd->cmd == NULL)
		clear_all_malloc_failed(minishell);
	while (cmd->l_cmd != NULL)
	{
		cmd->cmd[i] = ft_strdup(cmd->l_cmd->content);
		if (cmd->cmd[i] == NULL)
			clear_all_malloc_failed(minishell);
		i ++;
		free(cmd->l_cmd->content);
		tmp = cmd->l_cmd->next;
		free(cmd->l_cmd);
		cmd->l_cmd = tmp;
	}
	cmd->cmd[i] = NULL;
}

char	*set_file(t_redi *tmp)
{
	int		i;
	char	*new_file;

	i = 0;
	while (tmp->file[i] == '<' || tmp->file[i] == '>')
		i ++;
	while (tmp->file[i] == ' ' || (tmp->file[i] >= 9 && tmp->file[i] <= 13))
		i ++;
	new_file = ft_strdup(&tmp->file[i]);
	free(tmp->file);
	return (new_file);
}

void	set_status(t_redi *file)
{
	if (file->file[0] == '>')
	{
		if (file->file[1] == '>')
		{
			file->status = APPEND;
		}
		else
			file->status = OUTPUT;
	}
	else if (file->file[0] == '<')
	{
		if (file->file[1] == '<')
		{
			file->status = HEREDOC;
		}
		else
			file->status = INPUT;
	}
}

void	set_redi(t_cmd *cmd, t_mini *minishell)
{
	t_redi	*tmp;

	tmp = cmd->file;
	while (tmp != NULL)
	{
		set_status(tmp);
		tmp->file = set_file(tmp);
		if (tmp->file == NULL)
			clear_all_malloc_failed(minishell);
		tmp = tmp->next;
	}
}

void	add_null_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		tmp->l_cmd = NULL;
		tmp->cmd = NULL;
		tmp->file = NULL;
		tmp = tmp->next;
	}
}
