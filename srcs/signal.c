/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 06:53:03 by niromano          #+#    #+#             */
/*   Updated: 2023/11/15 07:09:00 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

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
	if (g_signal == 2 || g_signal == 4 || g_signal == 5)
	{
		if (g_signal == 4)
			dup2(minishell->stdin, 0);
		g_signal = 0;
		minishell->exit_status = 130;
	}
}
