/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:05:41 by niromano          #+#    #+#             */
/*   Updated: 2023/10/24 09:12:25 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_malloc_failed(t_env *env)
{
	clear_env(env);
	ft_putstr_fd("Malloc Failed !\n", 2);
	return (1);
}

void	free_all_line(t_cmd *cmd, t_env *env, char *s)
{
	t_cmd	*tmp;

	if (s != NULL)
		free(s);
	while (cmd->next != NULL)
	{
		free(cmd->line);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
	if (cmd->line != NULL)
		free(cmd->line);
	free(cmd);
	exit(print_malloc_failed(env));
}

void	init_last_cmd(t_cmd *cmd, t_cmd *start_cmd, t_env *env, char *s)
{
	cmd->line = ft_strdup(s);
	if (cmd->line == NULL)
		free_all_line(start_cmd, env, s);
	cmd->next = NULL;
	free(s);
}

t_cmd	*init_cmd(char *s, t_env *env)
{
	t_cmd	*start_cmd;
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		exit(print_malloc_failed(env));
	cmd->next = NULL;
	start_cmd = cmd;
	while (s[i] != '\0')
	{
		i = pass_quotes(s, i);
		if (s[i] == '|')
		{
			s = init_new_cmd(s, i, cmd);
			if (s == NULL)
				free_all_line(start_cmd, env, s);
			cmd = cmd->next;
			i = -1;
		}
		i ++;
	}
	init_last_cmd(cmd, start_cmd, env, s);
	return (start_cmd);
}

t_cmd	*parsing(char *s, t_mini minishell)
{
	t_cmd	*cmd;

	cmd = init_cmd(s, minishell.env);
	expend(cmd, minishell);
	return (cmd);
}
