/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:05:41 by niromano          #+#    #+#             */
/*   Updated: 2023/10/11 11:19:15 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	print_malloc_failed(t_env *env)
{
	clear_env(env);
	ft_putstr_fd("Malloc Failed !\n", 2);
	return (1);
}

static char	*copy(char *s, int i, t_cmd *cmd)
{
	int		j;
	char	*new_s;

	j = 0;
	cmd->line = malloc(sizeof(char) * (i + 1));
	if (cmd->line == NULL)
	{
		free(s);
		return (NULL);
	}
	while (j != i)
	{
		cmd->line[j] = s[j];
		j ++;
	}
	cmd->line[j] = '\0';
	new_s = ft_strdup(&s[i + 1]);
	if (new_s == NULL)
	{
		free(cmd->line);
		free(s);
		return (NULL);
	}
	free(s);
	return (new_s);
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

t_cmd	*init_cmd(char *s, t_env *env)
{
	t_cmd	*start_cmd;
	t_cmd	*cmd;
	t_cmd	*add_cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		exit(print_malloc_failed(env));
	cmd->next = NULL;
	start_cmd = cmd;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i ++;
			while (s[i] != '\'')
				i ++;
		}
		else if (s[i] == '\"')
		{
			i ++;
			while (s[i] != '\"')
				i ++;
		}
		else if (s[i] == '|')
		{
			s = copy(s, i, cmd);
			if (s == NULL)
				free_all_line(start_cmd, env, s);
			add_cmd = malloc(sizeof(t_cmd));
			if (add_cmd == NULL)
				free_all_line(start_cmd, env, s);
			add_cmd->next = NULL;
			cmd->next = add_cmd;
			cmd = cmd->next;
			i = -1;
		}
		i ++;
	}
	cmd->line = ft_strdup(s);
	if (cmd->line == NULL)
		free_all_line(start_cmd, env, s);
	cmd->next = NULL;
	free(s);
	return (start_cmd);
}

t_cmd	*parsing(char *s, t_env *env)
{
	t_cmd	*cmd;

	cmd = init_cmd(s, env);
	expend(cmd, env);
	return (cmd);
}
