/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:19:42 by niromano          #+#    #+#             */
/*   Updated: 2023/10/20 06:51:55 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redi	*f_tmp;
	int		i;

	while (cmd != NULL)
	{
		i = 0;
		while (cmd->file != NULL)
		{
			free(cmd->file->file);
			f_tmp = cmd->file;
			cmd->file = cmd->file->next;
			free(f_tmp);
		}
		while (cmd->cmd[i] != NULL)
		{
			free(cmd->cmd[i]);
			i ++;
		}
		free(cmd->cmd);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

int	prompt(t_env *env)
{
	const char	*prompt = "minishell$ ";
	char		*s;
	t_cmd		*cmd;

	while (1)
	{
		s = readline(prompt);
		if (s == NULL)
		{
			printf("exit\n");
			clear_env(env);
			exit(0);
		}
		if (s[0] != '\0')
			add_history(s);
		if (syntax_error_check(s) == 0)
		{
			cmd = parsing(s, env);
			treatment_cmd(cmd, env);
			exec(cmd, env);
			clear_cmd(cmd);
		}
		else
			free(s);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*own_env;

	(void)argc;
	(void)argv;
	if (env[0] == NULL)
		own_env = create_without_env();
	else
		own_env = create_own_env(env);
	add_shlvl(own_env);
	prompt(own_env);
	return (0);
}
