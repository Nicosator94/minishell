/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:07:07 by niromano          #+#    #+#             */
/*   Updated: 2023/10/12 10:48:48 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*init_new_cmd(char *s, int i, t_cmd *cmd)
{
	t_cmd	*add_cmd;
	char	*new_s;

	new_s = copy(s, i, cmd);
	if (new_s == NULL)
		return (NULL);
	add_cmd = malloc(sizeof(t_cmd));
	if (add_cmd == NULL)
	{
		free(new_s);
		return (NULL);
	}
	add_cmd->next = NULL;
	cmd->next = add_cmd;
	return (new_s);
}

int	pass_quotes(char *s, int i)
{
	char	c;

	if (s[i] == '\'' || s[i] == '\"')
	{
		c = s[i++];
		while (s[i] != c)
			i ++;
	}
	return (i);
}
