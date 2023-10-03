/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:05:41 by niromano          #+#    #+#             */
/*   Updated: 2023/10/03 12:15:34 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*copy(char *s, int i, t_cmd *cmd)
{
	int		j;
	char	*new_s;

	j = 0;
	cmd->cmd = malloc(sizeof(char) * (i + 1));
	while (j != i)
	{
		cmd->cmd[j] = s[j];
		j ++;
	}
	cmd->cmd[j] = '\0';
	new_s = ft_strdup(&s[i + 1]);
	free(s);
	return (new_s);
}

t_cmd	*init_cmd(char *s)
{
	t_cmd	*start_cmd;
	t_cmd	*cmd;
	t_cmd	*add_cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
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
			add_cmd = malloc(sizeof(t_cmd));
			cmd->next = add_cmd;
			cmd = cmd->next;
			i = -1;
		}
		i ++;
	}
	cmd->cmd = ft_strdup(s);
	cmd->next = NULL;
	free(s);
	return (start_cmd);
}

t_cmd	*parsing(char *s, t_env *env)
{
	t_cmd	*cmd;

	cmd = init_cmd(s);
	expend(cmd, env);
	return (cmd);
}
