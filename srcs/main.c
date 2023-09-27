/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:19:42 by niromano          #+#    #+#             */
/*   Updated: 2023/09/27 15:55:05 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec(char *cmd, char **env)
{
	pid_t	pid;
	char	*path = "/usr/bin/clear";
	char	**cmd1;

	(void)cmd;
	cmd1 = malloc(sizeof(char *) * 2);
	cmd1[0] = "clear";
	cmd1[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd1, env);
		printf("error\n");
		exit(0);
	}
	if (pid != 0)
		wait(NULL);
}

int parsing(char *s, char **env)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(s, ' ');
	while (cmd[i] != NULL)
	{
		printf("%d = %s\n", i, cmd[i]);
		i ++;
	}
	exec(cmd[0], env);
	i = 0;
	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		i ++;
	}
	free(cmd);
	return (0);
}

int	prompt(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	const char *prompt = "minishell$ ";
	char	*s;
	char	*lim;

	lim = "exit";
	s = malloc(1);
	while (ft_strncmp(s, lim, 5) != 0)
	{
		free(s);
		s = readline(prompt);
		if (s[0] != '\0')
			add_history(s);
		if (ft_strncmp(s, lim, 5) != 0)
			parsing(s, env);
	}
	printf("%s\n", s);
	free(s);
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	// char **env;

	// env = set_env();
	prompt(argc, argv, env);
	return (0);
}
