/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:23 by niromano          #+#    #+#             */
/*   Updated: 2023/11/14 07:39:07 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin(char *main_cmd)
{
	if (main_cmd == NULL)
		return (1);
	if (ft_strncmp(main_cmd, "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(main_cmd, "cd", 3) == 0)
		return (0);
	else if (ft_strncmp(main_cmd, "pwd", 4) == 0)
		return (0);
	else if (ft_strncmp(main_cmd, "export", 7) == 0)
		return (0);
	else if (ft_strncmp(main_cmd, "unset", 6) == 0)
		return (0);
	else if (ft_strncmp(main_cmd, "env", 4) == 0)
		return (0);
	else if (ft_strncmp(main_cmd, "exit", 5) == 0)
		return (0);
	return (1);
}

int	do_builtin(t_cmd *cmd, t_mini *minishell)
{
	int	infile;
	int	outfile;
	int	real_outfile;

	infile = take_infile(cmd, -2);
	if (infile == -1)
	{
		minishell->exit_status = 1;
		return (1);
	}
	else if (infile > -1)
		close(infile);
	outfile = take_outfile(cmd, 1);
	real_outfile = open("/dev/stdout", O_WRONLY);
	if (outfile == -1)
	{
		if (real_outfile > 0)
			close(real_outfile);
		minishell->exit_status = 1;
		return (1);
	}
	dup2(outfile, 1);
	close(outfile);
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		my_echo(cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		cd(cmd->cmd, &minishell->env);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		export(cmd->cmd, &minishell->env);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		unset(cmd->cmd, &minishell->env);
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		my_env(minishell->env);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		my_exit(cmd->cmd, minishell->env);
	if (real_outfile > 0)
	{
		dup2(real_outfile, 1);
		close(real_outfile);
	}
	minishell->exit_status = 0;
	return (0);
}

void	do_builtin_in_exec(t_cmd *cmd, t_mini *minishell)
{
	int	res;

	res = 0;
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		my_echo(cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		cd(cmd->cmd, &minishell->env);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		export(cmd->cmd, &minishell->env);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		unset(cmd->cmd, &minishell->env);
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		my_env(minishell->env);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		my_exit(cmd->cmd, minishell->env);
	if (res == -2)
		clear_all_malloc_failed(minishell);
	exit(res);
}
