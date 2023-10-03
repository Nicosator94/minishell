/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:28:16 by niromano          #+#    #+#             */
/*   Updated: 2023/10/03 13:00:03 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	exec(t_cmd *cmd, t_env *env)
// {
// 	int	fdin;
// 	int	fdout;

// 	fdin = open("/dev/stdin", O_RDONLY);
// 	while (cmd->next != NULL)
// 	{
// 		fdin = execute(cmd->cmd, env, fdin);
// 		cmd = cmd->next;
// 	}
// 	fdout = open("/dev/stdout", O_WRONLY);
// 	last_execute(cmd->cmd, env);
// }
