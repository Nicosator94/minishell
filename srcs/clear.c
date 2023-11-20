/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:12:14 by niromano          #+#    #+#             */
/*   Updated: 2023/11/20 13:20:54 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_all_malloc_failed(t_mini *minishell)
{
	if (minishell->stdin > -1)
		close(minishell->stdin);
	if (minishell->stdout > -1)
		close(minishell->stdout);
	if (minishell->env != NULL)
		clear_env(minishell->env);
	if (minishell->cmd != NULL)
		clear_cmd(minishell->cmd);
	if (minishell != NULL)
		free(minishell);
	rl_clear_history();
	ft_putstr_fd("Malloc Failed !\n", 2);
	exit(1);
}

void	clear_all(t_mini *minishell)
{
	if (minishell->stdin > -1)
		close(minishell->stdin);
	if (minishell->stdout > -1)
		close(minishell->stdout);
	if (minishell->env != NULL)
		clear_env(minishell->env);
	if (minishell->cmd != NULL)
		clear_cmd(minishell->cmd);
	if (minishell != NULL)
		free(minishell);
	rl_clear_history();
}
