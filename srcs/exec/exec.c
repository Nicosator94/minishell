/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:07:38 by niromano          #+#    #+#             */
/*   Updated: 2023/10/23 10:47:53 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_failed(t_cmd *cmd, t_env *env, char *path, char **mat_env)
{
	int	i;

	i = 0;
	all_free(env, cmd);
	if (path != NULL)
		free(path);
	while (mat_env[i] != NULL && mat_env != NULL)
	{
		free(mat_env[i]);
		i ++;
	}
	if (mat_env != NULL)
		free(mat_env);
	exit(0);
}

void	print_failed(char *cmd)
{
	int	i;
	int	trig;

	i = 0;
	trig = 0;
	if (cmd == NULL)
		return ;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			trig = 1;
		i ++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (trig == 0)
		ft_putstr_fd(": command not found\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
}

int	exec_cmd(t_cmd *cmd, t_env **env, int tmp_file, t_cmd *start_cmd)
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
	if (file[0] == -1 || file[1] == -1)
	{
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
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
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
		{
			do_builtin(cmd, env, 0);
			all_free(*env, start_cmd);
			exit(0);
		}
		mat_env = list_to_matrix(*env, start_cmd);
		path = get_path(cmd->cmd[0], *env);
		if (path != NULL && mat_env != NULL)
			execve(path, cmd->cmd, mat_env);
		print_failed(cmd->cmd[0]);
		exec_failed(start_cmd, *env, path, mat_env);
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

void	exec(t_cmd *cmd, t_env **env)
{
	t_cmd	*tmp;
	int		tmp_file;

	tmp = cmd;
	tmp_file = -2;
	if (tmp->next == NULL && check_builtin(cmd->cmd[0]) == 0)
		do_builtin(cmd, env, 1);
	else
	{
		while (tmp != NULL)
		{
			tmp_file = exec_cmd(tmp, env, tmp_file, cmd);
			tmp = tmp->next;
		}
		clean_here_doc(cmd);
		wait_all(cmd);
	}
}
