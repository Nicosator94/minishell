/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:07:38 by niromano          #+#    #+#             */
/*   Updated: 2023/10/12 11:52:19 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(t_cmd *cmd, t_env *env)
{
	t_cmd	*tmp;

	tmp = cmd;
	(void)env;
	while (tmp != NULL && tmp->cmd[0] != NULL)
	{
		if (ft_strncmp(tmp->cmd[0], "echo", 5) == 0)
			my_echo(cmd->cmd);
		else if (ft_strncmp(tmp->cmd[0], "cd", 3) == 0)
			cd(cmd->cmd, env);
		else if (ft_strncmp(tmp->cmd[0], "pwd", 4) == 0)
			pwd(cmd->cmd);
		else if (ft_strncmp(tmp->cmd[0], "export", 7) == 0)
			export(cmd->cmd, env);
		else if (ft_strncmp(tmp->cmd[0], "unset", 6) == 0)
			unset(cmd->cmd, &env);
		else if (ft_strncmp(tmp->cmd[0], "env", 4) == 0)
			my_env(cmd->cmd, env);
		else if (ft_strncmp(tmp->cmd[0], "exit", 5) == 0)
			my_exit(cmd->cmd, env);
		tmp = tmp->next;
	}
}
