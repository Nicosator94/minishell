/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:51:12 by niromano          #+#    #+#             */
/*   Updated: 2023/10/09 13:59:26 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	separate_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->line[i] == ' ' || (cmd->line[i] >= 9 && cmd->line[i] <= 13))
		i ++;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == '<' || cmd->line[i] == '>')
			i = get_file(cmd, i);
		else
			i = get_command(cmd, i);
		while ((cmd->line[i] == ' ' || (cmd->line[i] >= 9 && cmd->line[i] <= 13)) && cmd->line[i] != '\0')
			i ++;
	}
	free(cmd->line);
}

void	fill_mat_of_cmd(t_cmd *cmd)
{
	int		i;
	t_list	*tmp;

	i = 0;
	cmd->cmd = malloc(sizeof(char *) * (ft_lstsize(cmd->l_cmd) + 1));
	while (cmd->l_cmd != NULL)
	{
		cmd->cmd[i] = ft_strdup(cmd->l_cmd->content);
		i ++;
		free(cmd->l_cmd->content);
		tmp = cmd->l_cmd->next;
		free(cmd->l_cmd);
		cmd->l_cmd = tmp;
	}
	cmd->cmd[i] = NULL;
}

char	*set_file(t_cmd *cmd)
{
	int		i;
	char	*new_file;

	i = 0;
	while (cmd->file->file[i] == '<' || cmd->file->file[i] == '>')
		i ++;
	while (cmd->file->file[i] == ' ' || (cmd->file->file[i] >= 9 && cmd->file->file[i] <= 13))
		i ++;
	new_file = ft_strdup(&cmd->file->file[i]);
	free(cmd->file->file);
	return (new_file);
}

void	set_redi(t_cmd *cmd)
{
	if (cmd->file->file[0] == '>')
	{
		if (cmd->file->file[1] == '>')
		{
			cmd->file->status = APPEND;
		}
		else
			cmd->file->status = OUTPUT;
	}
	else if (cmd->file->file[0] == '<')
	{
		if (cmd->file->file[1] == '<')
		{
			cmd->file->status = HEREDOC;
		}
		else
			cmd->file->status = INPUT;
	}
	cmd->file->file = set_file(cmd);
}

char	*rm(char *s, int start, int end)
{
	int		i;
	char	*new_s;

	i = 0;
	new_s = malloc(sizeof(char) * (ft_strlen(s) - 1));
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

void	remove_quotes(t_cmd *cmd)
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
				j -= 2;
			}
			else if (cmd->cmd[i][j] == '\"')
			{
				start = j;
				j ++;
				while (cmd->cmd[i][j] != '\"')
					j ++;
				cmd->cmd[i] = rm(cmd->cmd[i], start, j);
				j -= 2;
			}
			j ++;
		}
		i ++;
	}
}

void	treatment_cmd(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		cmd->file = NULL;
		cmd->l_cmd = NULL;
		separate_cmd(cmd);
		fill_mat_of_cmd(cmd);
		if (cmd->file != NULL)
			set_redi(cmd);
		remove_quotes(cmd);
		cmd = cmd->next;
	}
}
