/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:17:45 by niromano          #+#    #+#             */
/*   Updated: 2023/10/24 11:28:17 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*copy(char *s, int i)
{
	char	*cpy;
	int		j;

	j = 0;
	cpy = malloc(sizeof(char) * (i + 1));
	if (cpy == NULL)
		return (NULL);
	while (j != i)
	{
		cpy[j] = s[j];
		j ++;
	}
	cpy[j] = '\0';
	return (cpy);
}

void	clear_for_failed(t_env *env, t_cmd *cmd, char *s)
{
	t_cmd	*tmp;

	if (s != NULL)
		free(s);
	clear_env(env);
	while (cmd != NULL)
	{
		free(cmd->line);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
	ft_putstr_fd("Malloc Failed !\n", 2);
	exit(1);
}

char	*replace_with_env(char *s, int i, t_mini *minishell, t_cmd *cmd)
{
	char	*new_cmd;
	char	*tmp1;
	char	*tmp2;
	int		len;

	tmp1 = copy(s, i);
	if (tmp1 == NULL)
		clear_for_failed(minishell->env, cmd, NULL);
	i ++;
	len = dollar_len(s, i);
	tmp2 = copy(&s[i], len);
	if (tmp2 == NULL)
		clear_for_failed(minishell->env, cmd, tmp1);
	tmp2 = replace(tmp2, minishell->env, &minishell->exit_status);
	if (tmp2 == NULL)
		clear_for_failed(minishell->env, cmd, tmp1);
	new_cmd = replace_with_env_utils(&s[i + len], tmp1, tmp2);
	if (new_cmd == NULL)
		clear_for_failed(minishell->env, cmd, NULL);
	free(s);
	return (new_cmd);
}

void	expend_utils(t_cmd *cmd, t_cmd *start_cmd, t_mini *minishell, int count)
{
	int	i;

	i = 0;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == '\"')
			count += 1;
		if (cmd->line[i] == '\'' && count % 2 == 0)
		{
			i ++;
			while (cmd->line[i] != '\'')
				i ++;
		}
		else if (cmd->line[i] == '$'
			&& ((cmd->line[i + 1] >= 'a' && cmd->line[i + 1] <= 'z')
				|| (cmd->line[i + 1] >= 'A' && cmd->line[i + 1] <= 'Z')
				|| cmd->line[i + 1] == '_' || cmd->line[i + 1] == '?'))
		{
			cmd->line = replace_with_env(cmd->line, i, minishell, start_cmd);
			i = -1;
			count = 0;
		}
		i ++;
	}
}

void	expend(t_cmd *cmd, t_mini *minishell)
{
	int		count;
	t_cmd	*start_cmd;

	count = 0;
	start_cmd = cmd;
	while (cmd != NULL)
	{
		expend_utils(cmd, start_cmd, minishell, count);
		cmd = cmd->next;
	}
}
