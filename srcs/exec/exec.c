/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:07:38 by niromano          #+#    #+#             */
/*   Updated: 2023/11/21 11:27:27 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prep_dup(int file[2], int tube[2])
{
	if (file[0] == -1 || file[1] == -1)
	{
		if (file[0] > 0)
			close(file[0]);
		if (file[1] > 0)
			close(file[1]);
		close(tube[1]);
		close(tube[0]);
		exit(1);
	}
	close(tube[0]);
	if (file[0] > 0)
	{
		dup2(file[0], 0);
		close(file[0]);
	}
	if (file[1] > 0)
	{
		dup2(file[1], 1);
		close(file[1]);
	}
	else
		dup2(tube[1], 1);
	close(tube[1]);
	return ;
}

void	do_exec(t_cmd *cmd, t_mini *minishell)
{
	char	**mat_env;
	char	*path;

	if (check_builtin(cmd->cmd[0]) == 0)
		do_builtin_in_exec(cmd, minishell);
	mat_env = list_to_matrix(minishell);
	path = get_path(cmd->cmd[0], minishell);
	if (path != NULL && mat_env != NULL)
	{
		close(minishell->stdin);
		close(minishell->stdout);
		execve(path, cmd->cmd, mat_env);
	}
	exec_failed(minishell, path, mat_env, cmd->cmd[0]);
}

int	exec_cmd(t_cmd *cmd, t_mini *minishell, int tmp_file)
{
	int		file[2];
	int		tube[2];

	pipe(tube);
	file[0] = take_infile(cmd, tmp_file);
	if (cmd->next != NULL)
		file[1] = take_outfile(cmd, 0);
	else
		file[1] = take_outfile(cmd, 1);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		prep_dup(file, tube);
		do_exec(cmd, minishell);
	}
	if (file[0] > 0)
		close(file[0]);
	if (file[1] > 0)
		close(file[1]);
	close(tube[1]);
	if (cmd->next != NULL)
		return (tube[0]);
	close(tube[0]);
	return (-1);
}

void	exec(t_mini *minishell)
{
	t_cmd	*tmp;
	int		tmp_file;

	tmp = minishell->cmd;
	tmp_file = -2;
	if (tmp->next == NULL && check_builtin(tmp->cmd[0]) == 0)
	{
		if (do_builtin(tmp, minishell) == -2)
			clear_all_malloc_failed(minishell);
	}
	else
	{
		g_signal = 1;
		while (tmp != NULL)
		{
			tmp_file = exec_cmd(tmp, minishell, tmp_file);
			tmp = tmp->next;
		}
		wait_all(minishell);
		if (g_signal != 2 && g_signal != 10)
			g_signal = 0;
	}
}
