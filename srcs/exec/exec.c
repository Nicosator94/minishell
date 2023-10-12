/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:07:38 by niromano          #+#    #+#             */
/*   Updated: 2023/10/12 16:29:34 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	take_infile(t_cmd *cmd)
{
	t_redi	*tmp;
	int		infile;

	infile = open("/dev/stdin", O_RDONLY);
	tmp = cmd->file;
	while (tmp != NULL)
	{
		if (tmp->status == 1)
		{
			close(infile);
			infile = open(tmp->file, O_RDONLY);
		}
		else if (tmp->status == 3)
		{
			close(infile);
			// here doc
		}
		tmp = tmp->next;
	}
	return (infile);
}

int	take_outfile(t_cmd *cmd)
{
	t_redi	*tmp;
	int		outfile;

	outfile = open("/dev/stdout", O_WRONLY);
	tmp = cmd->file;
	while (tmp != NULL)
	{
		if (tmp->status == 2)
		{
			close(outfile);
			outfile = open(tmp->file, O_WRONLY | O_TRUNC);
		}
		else if (tmp->status == 4)
		{
			close(outfile);
			outfile = open(tmp->file, O_WRONLY | O_APPEND);
		}
		tmp = tmp->next;
	}
	return (outfile);
}

char	**get_list_of_path(t_env *env)
{
	char	**list_of_path;
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL && ft_strncmp(tmp->name, "PATH", 5) != 0)
		tmp = tmp->next;
	if (ft_strncmp(tmp->name, "PATH", 5) == 0)
	{
		list_of_path = ft_split(tmp->value, ':');
		return (list_of_path);
	}
	return (NULL);
}

void	free_get_path(char **path_of_env, char *tmp)
{
	int	i;

	i = 0;
	while (path_of_env[i] != NULL && path_of_env != NULL)
	{
		free(path_of_env[i]);
		i ++;
	}
	if (path_of_env != NULL)
		free(path_of_env);
	if (tmp != NULL)
		free(tmp);
}

char	*get_path(char *cmd, t_env *env)
{
	char	*path;
	char	**path_of_env;
	char	*tmp;
	int		i;

	i = 0;
	if (cmd[0] == '.' || cmd[0] == '/')
		return(ft_strdup(cmd));
	path_of_env = get_list_of_path(env);
	tmp = ft_strjoin("/", cmd);
	while (path_of_env[i] != NULL)
	{
		path = ft_strjoin(path_of_env[i], tmp);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_get_path(path_of_env, tmp);
			return (path);
		}
		free(path);
		i ++;
	}
	free_get_path(path_of_env, tmp);
	return (NULL);
}

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

void	exec_cmd(t_cmd *cmd, t_env *env)
{
	int		infile;
	int		outfile;
	char	*path;
	char	**mat_env;
	pid_t	pid;

	infile = take_infile(cmd);
	outfile = take_outfile(cmd);
	pid = fork();
	if (pid == 0)
	{
		dup2(infile, 0);
		dup2(outfile, 1);
		close(infile);
		close(outfile);
		path = get_path(cmd->cmd[0], env);
		mat_env = list_to_matrix(env);
		if (path != NULL && mat_env != NULL)
			execve(path, cmd->cmd, mat_env);
		exec_failed(cmd, env, path, mat_env);
	}
	close(infile);
	close(outfile);
}

void	wait_all(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		wait(NULL);
		tmp = tmp->next;
	}
}

void	exec(t_cmd *cmd, t_env *env)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		exec_cmd(tmp, env);
		tmp = tmp->next;
	}
	wait_all(cmd);
}

// void	exec(t_cmd *cmd, t_env *env)
// {
// 	t_cmd	*tmp;

// 	tmp = cmd;
// 	while (tmp != NULL && tmp->cmd[0] != NULL)
// 	{
// 		if (ft_strncmp(tmp->cmd[0], "echo", 5) == 0)
// 			my_echo(tmp->cmd);
// 		else if (ft_strncmp(tmp->cmd[0], "cd", 3) == 0)
// 			cd(tmp->cmd, env);
// 		else if (ft_strncmp(tmp->cmd[0], "pwd", 4) == 0)
// 			pwd(tmp->cmd);
// 		else if (ft_strncmp(tmp->cmd[0], "export", 7) == 0)
// 			export(tmp->cmd, env);
// 		else if (ft_strncmp(tmp->cmd[0], "unset", 6) == 0)
// 			unset(tmp->cmd, &env);
// 		else if (ft_strncmp(tmp->cmd[0], "env", 4) == 0)
// 			my_env(tmp->cmd, env);
// 		else if (ft_strncmp(tmp->cmd[0], "exit", 5) == 0)
// 			my_exit(tmp->cmd, env);
// 		tmp = tmp->next;
// 	}
// }
