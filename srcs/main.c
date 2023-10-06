/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:19:42 by niromano          #+#    #+#             */
/*   Updated: 2023/10/06 09:31:48 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	affiche_cmd(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd != NULL)
	{
		printf("cmd %d : %s\n", i, cmd->line);
		cmd = cmd->next;
		i ++;
	}
}

void	clear_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		free(cmd->line);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

int	prompt(char **env)
{
	const char	*prompt = "minishell$ ";
	char		*s;
	t_cmd		*cmd;
	t_env		*own_env;

	if (env[0] == NULL)
		own_env = create_without_env();
	else
		own_env = create_own_env(env);
	while (1)
	{
		s = readline(prompt);
		if (s == NULL)
		{
			printf("exit\n");
			clear_env(own_env);
			exit(0);
		}
		if (s[0] != '\0')
			add_history(s);
		if (syntax_error_check(s) == 0)
		{
			cmd = parsing(s, own_env);
			treatment_cmd(cmd);
			affiche_cmd(cmd);
			clear_cmd(cmd);
		}
		else
			free(s);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	prompt(env);
	return (0);
}
