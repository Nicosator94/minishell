/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:11:11 by niromano          #+#    #+#             */
/*   Updated: 2023/11/21 15:11:40 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*remove_quotes_utils(char *cmd, t_mini *minishell)
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
				clear_all_malloc_failed(minishell);
			i -= 2;
		}
		i ++;
	}
	return (cmd);
}

void	remove_quotes(t_cmd *cmd, t_mini *minishell)
{
	int		i;

	i = 0;
	while (cmd->cmd[i] != NULL)
	{
		cmd->cmd[i] = remove_quotes_utils(cmd->cmd[i], minishell);
		i ++;
	}
}
