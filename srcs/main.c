/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:19:42 by niromano          #+#    #+#             */
/*   Updated: 2023/10/06 16:16:06 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	affiche_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redi	*f_tmp;
	t_list	*c_tmp;
	int		i = 1;
	int		j = 1;

	tmp = cmd;
	while (tmp != NULL)
	{
		f_tmp = tmp->file;
		while (f_tmp != NULL)
		{
			printf(" = %d\nn = %d\ns = %s\n\n", i, j, f_tmp->file);
			j ++;
			f_tmp = f_tmp->next;
		}
		j = 1;
		printf("-------------------------------------------------------------\n");
		c_tmp = tmp->l_cmd;
		while (c_tmp != NULL)
		{
			printf("p = %d\nn = %d\ns = %s\n\n", i, j, c_tmp->content);
			j ++;
			c_tmp = c_tmp->next;
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
	t_list	*c_tmp;

	while (cmd != NULL)
	{
		while (cmd->file != NULL)
		{
			free(cmd->file->file);
			f_tmp = cmd->file;
			cmd->file = cmd->file->next;
			free(f_tmp);
		}
		while (cmd->l_cmd != NULL)
		{
			free(cmd->l_cmd->content);
			c_tmp = cmd->l_cmd;
			cmd->l_cmd = cmd->l_cmd->next;
			free(c_tmp);
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
