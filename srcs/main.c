/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:19:42 by niromano          #+#    #+#             */
/*   Updated: 2023/11/20 13:14:50 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*take_line(t_mini *minishell)
{
	char	*s;
	char	*line;

	check_signal(minishell);
	if (isatty(0) == 1)
		s = readline("minishell$ ");
	else
	{
		line = get_next_line(0, NULL);
		s = ft_strtrim(line, "\n");
		free(line);
	}
	check_signal(minishell);
	return (s);
}

void	pre_exec(char *s, t_mini *minishell)
{
	if (syntax_error_check(s) == 0)
	{
		minishell->cmd = parsing(s, minishell);
		treatment_cmd(minishell);
		expend(minishell);
		if (g_signal != 4)
			exec(minishell);
		clear_cmd(minishell->cmd);
		minishell->cmd = NULL;
	}
	else
	{
		if (check_spaces(s) == 0)
			minishell->exit_status = 2;
		free(s);
	}
}

int	prompt(t_mini *minishell)
{
	char	*s;
	int		exit_value;

	while (1)
	{
		s = take_line(minishell);
		if (s == NULL)
		{
			if (isatty(0) == 1)
				printf("exit\n");
			exit_value = minishell->exit_status;
			clear_all(minishell);
			exit(exit_value);
		}
		if (s[0] != '\0')
			add_history(s);
		pre_exec(s, minishell);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*minishell;

	(void)argc;
	(void)argv;
	signal(SIGINT, &sigint);
	signal(SIGQUIT, &sigquit);
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
	minishell->stdin = dup(0);
	minishell->stdout = dup(1);
	prompt(minishell);
	return (0);
}
