/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:19:42 by niromano          #+#    #+#             */
/*   Updated: 2023/10/12 11:37:01 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	affiche_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redi	*f_tmp;
	int		i;

	tmp = cmd;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->cmd[i] != NULL)
			printf("Commandes =\n");
		while (tmp->cmd[i] != NULL)
		{
			printf("		%s\n", tmp->cmd[i]);
			i ++;
		}
		f_tmp = tmp->file;
		if (f_tmp != NULL)
			printf("Redirection =\n1 = INP / 2 = OUT / 3 = HERED / 4 = APP\n");
		while (f_tmp != NULL)
		{
			printf("		 %d = %s\n", f_tmp->status, f_tmp->file);
			f_tmp = f_tmp->next;
		}
		printf("----------------------------------------------------------\n");
		tmp = tmp->next;
	}
}

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
			// affiche_cmd(cmd);
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
	prompt(own_env);
	return (0);
}
