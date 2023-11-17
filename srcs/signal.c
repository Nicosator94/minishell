/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 06:53:03 by niromano          #+#    #+#             */
/*   Updated: 2023/11/17 07:35:10 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

void	sigquit(int code)
{
	(void)code;
	if (g_signal == 1)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 10;
	}
	else
	{
		rl_on_new_line();
		printf("\33[2K\r");
		rl_redisplay();
	}
}

void	sigint(int code)
{
	(void)code;
	printf("\n");
	if (g_signal == 1)
	{
		rl_replace_line("", 0);
		g_signal = 2;
	}
	else if (g_signal == 3)
	{
		close(0);
		g_signal = 4;
	}
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		g_signal = 5;
	}
	rl_redisplay();
}

void	check_signal(t_mini *minishell)
{
	if (g_signal == 2 || g_signal == 4 || g_signal == 5 || g_signal == 10)
	{
		if (g_signal == 4)
			dup2(minishell->stdin, 0);
		minishell->exit_status = 130;
		if (g_signal == 10)
			minishell->exit_status += 1;
		g_signal = 0;
	}
}
