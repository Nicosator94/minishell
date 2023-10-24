/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:06:23 by niromano          #+#    #+#             */
/*   Updated: 2023/10/23 09:06:55 by niromano         ###   ########.fr       */
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

void	do_builtin(t_cmd *cmd, t_env **env, int trigger)
{
	int	outfile;
	int	real_outfile;

	if (trigger == 1)
	{
		outfile = take_outfile(cmd, 1);
		real_outfile = open("/dev/stdout", O_WRONLY);
		dup2(outfile, 1);
		close(outfile);
	}
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		my_echo(cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		cd(cmd->cmd, *env);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		pwd(cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		export(cmd->cmd, *env);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		unset(cmd->cmd, env);
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		my_env(cmd->cmd, *env);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		my_exit(cmd->cmd, *env);
	if (trigger == 1)
	{
		dup2(real_outfile, 1);
		close(real_outfile);
	}
}
