/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:19:42 by niromano          #+#    #+#             */
/*   Updated: 2023/10/25 11:56:04 by niromano         ###   ########.fr       */
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
			treatment_cmd(minishell);
			exec(minishell);
			clear_cmd(minishell->cmd);
			minishell->cmd = NULL;
		}
		else
			free(s);
	}
	return (0);
}

void	sigint()
{
	printf("\nminishell$ ");
}

void	sigquit()
{
	printf("\n");
	rl_on_new_line();
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*minishell;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, &sigquit);
	signal(SIGINT, &sigint);
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
	minishell->cmd = NULL;
	prompt(minishell);
	return (0);
}
