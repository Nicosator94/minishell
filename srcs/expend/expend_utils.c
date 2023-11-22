/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 05:19:03 by niromano          #+#    #+#             */
/*   Updated: 2023/11/22 08:15:21 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_after_dollar(char **cmd, int j, int i, int count)
{
	if (cmd[j][i] == '$'
		&& ((cmd[j][i + 1] >= 'a' && cmd[j][i + 1] <= 'z')
			|| (cmd[j][i + 1] >= 'A' && cmd[j][i + 1] <= 'Z')
			|| cmd[j][i + 1] == '_' || cmd[j][i + 1] == '?'))
		return (1);
	else if (cmd[j][i] == '$' && count % 2 == 0
		&& (cmd[j][i + 1] == '\'' || cmd[j][i + 1] == '\"'))
		return (2);
	return (0);
}

int	single_quotes_pass(char **cmd, int j, int i, int count)
{
	if (cmd[j][i] == '\'' && count % 2 == 0)
	{
		i ++;
		while (cmd[j][i] != '\'')
			i ++;
	}
	return (i);
}

void	expend_utils(char **cmd, t_mini *minishell)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (cmd[j] != NULL)
	{
		while (cmd[j][i] != '\0')
		{
			if (cmd[j][i] == '\"')
				count += 1;
			i = single_quotes_pass(cmd, j, i, count);
			if (check_after_dollar(cmd, j, i, count) > 0)
			{
				cmd[j] = replace_with_env(cmd[j], i, minishell);
				i = -1;
				count = 0;
			}
			i ++;
		}
		i = 0;
		j ++;
	}
}
