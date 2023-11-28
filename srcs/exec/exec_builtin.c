/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:23 by niromano          #+#    #+#             */
/*   Updated: 2023/11/21 10:53:30 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin(t_cmd *cmd, t_mini *minishell)
{
	int	res;

	res = 0;
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		res = my_echo(cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		res = cd(cmd->cmd, &minishell->env);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		res = pwd();
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		res = export(cmd->cmd, &minishell->env);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		res = unset(cmd->cmd, &minishell->env);
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		res = my_env(minishell->env);
	return (res);
}

int	builtin_file(t_cmd *cmd, t_mini *minishell)
{
	int	infile;
	int	outfile;

	infile = take_infile(cmd, -2);
	if (infile == -1)
	{
		minishell->exit_status = 1;
		return (1);
	}
	else if (infile > -1)
		close(infile);
	outfile = take_outfile(cmd, 1);
	if (outfile == -1)
	{
		minishell->exit_status = 1;
		return (1);
	}
	dup2(outfile, 1);
	close(outfile);
	return (0);
}

int	res_exit(int res, t_mini *minishell)
{
	if (res == -1)
	{
		if (minishell->exit_status == 0)
			res = 1;
		else
			res = minishell->exit_status;
	}
	else if (res == -3)
	{
		res = minishell->exit_status;
		clear_all(minishell);
		exit(res);
	}
	else
	{
		clear_all(minishell);
		exit(res);
	}
	return (res);
}

int	do_builtin(t_cmd *cmd, t_mini *minishell)
{
	int	res;

	res = 0;
	if (builtin_file(cmd, minishell) == 1)
		return (1);
	if (ft_strncmp(cmd->cmd[0], "exit", 5) != 0)
		res = builtin(cmd, minishell);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
	{
		if (isatty(0) == 1)
			printf("exit\n");
		res = my_exit(cmd->cmd);
		res = res_exit(res, minishell);
	}
	dup2(minishell->stdout, 1);
	if (res == -2)
		clear_all_malloc_failed(minishell);
	minishell->exit_status = res;
	return (res);
}

void	do_builtin_in_exec(t_cmd *cmd, t_mini *minishell)
{
	int	res;

	res = 0;
	if (ft_strncmp(cmd->cmd[0], "exit", 5) != 0)
		res = builtin(cmd, minishell);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
	{
		res = my_exit(cmd->cmd);
		if (res == -1)
			res = 1;
		else if (res == -3)
		{
			res = minishell->exit_status;
			clear_all(minishell);
			exit(res);
		}
	}
	if (res == -2)
		clear_all_malloc_failed(minishell);
	clear_all(minishell);
	exit(res);
}
