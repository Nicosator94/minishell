/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:07:38 by niromano          #+#    #+#             */
/*   Updated: 2023/11/14 07:14:50 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	directory_check(char *cmd)
{
	(void)cmd;
	return (1);
}

int	print_failed(char *cmd)
{
	int	i;
	int	trig;

	i = 0;
	trig = 0;
	if (cmd == NULL)
		return (0);
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			trig = 1;
		i ++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (trig == 0)
	{
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	else if (directory_check(cmd) == 0)
	{
		ft_putstr_fd(": Is a directory\n", 2);
		return (126);
	}
	ft_putstr_fd(": No such file or directory\n", 2);
	return (127);
}

void	exec_failed(t_mini *minishell, char *path, char **mat_env, char *cmd)
{
	int	i;
	int	return_value;
  
	i = 0;
	if (path != NULL)
		free(path);
	while (mat_env[i] != NULL && mat_env != NULL)
	{
		free(mat_env[i]);
		i ++;
	}
	if (mat_env != NULL)
		free(mat_env);
	return_value = print_failed(cmd);
	clear_all(minishell);
	exit(return_value);
}

int	exec_cmd(t_cmd *cmd, t_mini *minishell, int tmp_file)
{
	int		file[2];
	char	*path;
	char	**mat_env;
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
		if (check_builtin(cmd->cmd[0]) == 0)
			do_builtin_in_exec(cmd, minishell);
		mat_env = list_to_matrix(minishell);
		path = get_path(cmd->cmd[0], minishell);
		if (path != NULL && mat_env != NULL)
			execve(path, cmd->cmd, mat_env);
		exec_failed(minishell, path, mat_env, cmd->cmd[0]);
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
		while (tmp != NULL)
		{
			tmp_file = exec_cmd(tmp, minishell, tmp_file);
			tmp = tmp->next;
		}
		wait_all(minishell);
	}
}
