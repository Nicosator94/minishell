/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:51:12 by niromano          #+#    #+#             */
/*   Updated: 2023/10/06 13:48:22 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_file(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '<' || s[i] == '>')
		i ++;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i ++;
	while (s[i] != '\0' && s[i] != '<' && s[i] != '>' && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
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
		i ++;
	}
	return (i);
}

char	*copy(char *s, int len)
{
	int		i;
	char	*cpy;
	
	i = 0;
	cpy = malloc(sizeof(char) * (len + 1));
	while (i != len)
	{
		cpy[i] = s[i];
		i ++;
	}
	cpy[i] = '\0';
	return (cpy);
}

void	add_redi(t_cmd *cmd, t_redi *add)
{
	t_redi	*tmp;

	if (cmd->file == NULL)
		cmd->file = add;
	else
	{
		tmp = cmd->file;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = add;
	}
}

void	separate_cmd(t_cmd *cmd)
{
	int		i;
	int		len;
	t_redi	*add;

	i = 0;
	while (cmd->line[i] == ' ' || (cmd->line[i] >= 9 && cmd->line[i] <= 13))
		i ++;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == '<' || cmd->line[i] == '>')
		{
			len = get_file(&cmd->line[i]);
			add = malloc(sizeof(t_redi));
			add->file = copy(&cmd->line[i], len);
			add->next = NULL;
			add_redi(cmd, add);
			i += len;
		}
		else
			i ++;
	}
	free(cmd->line);
}

void	treatment_cmd(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		cmd->file = NULL;
		separate_cmd(cmd);
		cmd = cmd->next;
	}
}
