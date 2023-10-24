/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:19:42 by niromano          #+#    #+#             */
/*   Updated: 2023/10/24 12:38:39 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	prompt(t_mini *minishell)
{
	const char	*prompt = "minishell$ ";
	char		*s;

	while (1)
	{
		s = readline(prompt);
		if (s == NULL)
		{
			printf("exit\n");
			clear_all(minishell);
			exit(0);
		}
		if (s[0] != '\0')
			add_history(s);
		if (syntax_error_check(s) == 0)
		{
			minishell->cmd = parsing(s, minishell);
			treatment_cmd(minishell->cmd, minishell->env);
			printf("before : %d\n", minishell->exit_status);
			exec(minishell->cmd, &minishell->env, &minishell->exit_status);
			printf("after : %d\n", minishell->exit_status);
			clear_cmd(minishell->cmd);
			minishell->cmd = NULL;
		}
		else
			free(s);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*minishell;

	(void)argc;
	(void)argv;
	minishell = malloc(sizeof(t_mini));
	if (minishell == NULL)
	{
		ft_putstr_fd("Malloc Failed !\n", 2);
		exit(1);
	}
	minishell->exit_status = 0;
	if (env[0] == NULL)
		minishell->env = create_without_env();
	else
		minishell->env = create_own_env(env);
	add_shlvl(minishell->env);
	prompt(minishell);
	return (0);
}
