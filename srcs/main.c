/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:19:42 by niromano          #+#    #+#             */
/*   Updated: 2023/10/06 11:41:14 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	affiche_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redi	*f_tmp;
	int		i = 1;
	int		j = 1;

	tmp = cmd;
	while (tmp != NULL)
	{
		f_tmp = tmp->file;
		while (f_tmp != NULL)
		{
			printf("%d = %d = %s\n", i, j, f_tmp->file);
			j ++;
			f_tmp = f_tmp->next;
		}
		i ++;
		j = 1;
		tmp = tmp->next;
	}
}

void	clear_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redi	*f_tmp;

	while (cmd != NULL)
	{
		while (cmd->file != NULL)
		{
			free(cmd->file->file);
			f_tmp = cmd->file;
			cmd->file = cmd->file->next;
			free(f_tmp);
		}
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
