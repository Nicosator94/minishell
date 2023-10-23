/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agomes-g <agomes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:51:12 by niromano          #+#    #+#             */
/*   Updated: 2023/10/19 04:07:49 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	separate_cmd(t_cmd *cmd, t_env *env, t_cmd *start_cmd)
{
	int		i;

	i = 0;
	while (cmd->line[i] == ' ' || (cmd->line[i] >= 9 && cmd->line[i] <= 13))
		i ++;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == '<' || cmd->line[i] == '>')
			i = get_file(cmd, i, env, start_cmd);
		else
			i = get_command(cmd, i, env, start_cmd);
		while ((cmd->line[i] == ' '
				|| (cmd->line[i] >= 9 && cmd->line[i] <= 13))
			&& cmd->line[i] != '\0')
			i ++;
	}
	free(cmd->line);
	cmd->line = NULL;
}

char	*rm(char *s, int start, int end)
{
	int		i;
	char	*new_s;

	i = 0;
	new_s = malloc(sizeof(char) * (ft_strlen(s) - 1));
	if (new_s == NULL)
		return (NULL);
	while (i != start)
	{
		new_s[i] = s[i];
		i ++;
	}
	while (i + 1 != end)
	{
		new_s[i] = s[i + 1];
		i ++;
	}
	while (s[i + 2] != '\0')
	{
		new_s[i] = s[i + 2];
		i ++;
	}
	new_s[i] = '\0';
	free(s);
	return (new_s);
}

char	*remove_quotes_utils(char *cmd, t_env *env, t_cmd *start_cmd)
{
	int		i;
	int		start;
	char	c;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			c = cmd[i];
			start = i;
			i ++;
			while (cmd[i] != c)
				i ++;
			cmd = rm(cmd, start, i);
			if (cmd == NULL)
				all_clear_command(env, start_cmd);
			i -= 2;
		}
		i ++;
	}
	return (cmd);
}

void	remove_quotes(t_cmd *cmd, t_env *env, t_cmd *start_cmd)
{
	int		i;

	i = 0;
	while (cmd->cmd[i] != NULL)
	{
		cmd->cmd[i] = remove_quotes_utils(cmd->cmd[i], env, start_cmd);
		i ++;
	}
}

void	treatment_cmd(t_cmd *cmd, t_env *env)
{
	t_cmd	*start_cmd;

	add_null_cmd(cmd);
	start_cmd = cmd;
	while (cmd != NULL)
	{
		separate_cmd(cmd, env, start_cmd);
		fill_mat_of_cmd(cmd, env, start_cmd);
		if (cmd->file != NULL)
			set_redi(cmd, env, start_cmd);
		remove_quotes(cmd, env, start_cmd);
		cmd = cmd->next;
	}
	create_here_doc(start_cmd, env);
}
