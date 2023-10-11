/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:51:12 by niromano          #+#    #+#             */
/*   Updated: 2023/10/11 15:02:16 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		while ((cmd->line[i] == ' ' || (cmd->line[i] >= 9 && cmd->line[i] <= 13)) && cmd->line[i] != '\0')
			i ++;
	}
	free(cmd->line);
	cmd->line = NULL;
}

void	fill_mat_of_cmd(t_cmd *cmd, t_env *env, t_cmd *start_cmd)
{
	int		i;
	t_list	*tmp;

	i = 0;
	cmd->cmd = malloc(sizeof(char *) * (ft_lstsize(cmd->l_cmd) + 1));
	if (cmd->cmd == NULL)
		all_clear_command(env, start_cmd);
	while (cmd->l_cmd != NULL)
	{
		cmd->cmd[i] = ft_strdup(cmd->l_cmd->content);
		if (cmd->cmd[i] == NULL)
			all_clear_command(env, start_cmd);
		i ++;
		free(cmd->l_cmd->content);
		tmp = cmd->l_cmd->next;
		free(cmd->l_cmd);
		cmd->l_cmd = tmp;
	}
	cmd->cmd[i] = NULL;
}

char	*set_file(t_redi *tmp)
{
	int		i;
	char	*new_file;

	i = 0;
	while (tmp->file[i] == '<' || tmp->file[i] == '>')
		i ++;
	while (tmp->file[i] == ' ' || (tmp->file[i] >= 9 && tmp->file[i] <= 13))
		i ++;
	new_file = ft_strdup(&tmp->file[i]);
	free(tmp->file);
	return (new_file);
}

void	set_redi(t_cmd *cmd, t_env *env, t_cmd *start_cmd)
{
	t_redi	*tmp;

	tmp = cmd->file;
	while (tmp != NULL)
	{
		if (tmp->file[0] == '>')
		{
			if (tmp->file[1] == '>')
			{
				tmp->status = APPEND;
			}
			else
				tmp->status = OUTPUT;
		}
		else if (tmp->file[0] == '<')
		{
			if (tmp->file[1] == '<')
			{
				tmp->status = HEREDOC;
			}
			else
				tmp->status = INPUT;
		}
		tmp->file = set_file(tmp);
		if (tmp->file == NULL)
			all_clear_command(env, start_cmd);
		tmp = tmp->next;
	}
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

void	remove_quotes(t_cmd *cmd, t_env *env, t_cmd *start_cmd)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	while (cmd->cmd[i] != NULL)
	{
		j = 0;
		while (cmd->cmd[i][j] != '\0')
		{
			if (cmd->cmd[i][j] == '\'')
			{
				start = j;
				j ++;
				while (cmd->cmd[i][j] != '\'')
					j ++;
				cmd->cmd[i] = rm(cmd->cmd[i], start, j);
				if (cmd->cmd[i] == NULL)
					all_clear_command(env, start_cmd);
				j -= 2;
			}
			else if (cmd->cmd[i][j] == '\"')
			{
				start = j;
				j ++;
				while (cmd->cmd[i][j] != '\"')
					j ++;
				cmd->cmd[i] = rm(cmd->cmd[i], start, j);
				if (cmd->cmd[i] == NULL)
					all_clear_command(env, start_cmd);
				j -= 2;
			}
			j ++;
		}
		i ++;
	}
}

void	add_null_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		tmp->l_cmd = NULL;
		tmp->cmd = NULL;
		tmp->file = NULL;
		tmp = tmp->next;
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
}
