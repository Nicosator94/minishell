/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:17:45 by niromano          #+#    #+#             */
/*   Updated: 2023/11/21 15:11:38 by niromano         ###   ########.fr       */
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

char	*replace_with_env(char *s, int i, t_mini *minishell)
{
	char	*new_cmd;
	char	*tmp1;
	char	*tmp2;
	int		len;

	tmp1 = copy(s, i);
	if (tmp1 == NULL)
		clear_all_malloc_failed(minishell);
	i ++;
	len = dollar_len(s, i);
	tmp2 = copy(&s[i], len);
	if (tmp2 == NULL)
	{
		free(tmp1);
		clear_all_malloc_failed(minishell);
	}
	tmp2 = replace(tmp2, minishell->env, &minishell->exit_status);
	if (tmp2 == NULL)
	{
		free(tmp1);
		clear_all_malloc_failed(minishell);
	}
	new_cmd = replace_with_env_utils(&s[i + len], tmp1, tmp2);
	if (new_cmd == NULL)
		clear_all_malloc_failed(minishell);
	free(s);
	return (new_cmd);
}

void	expend_utils(char **cmd, t_mini *minishell, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[j] != NULL)
	{
		while (cmd[j][i] != '\0')
		{
			if (cmd[j][i] == '\"')
				count += 1;
			if (cmd[j][i] == '\'' && count % 2 == 0)
			{
				i ++;
				while (cmd[j][i] != '\'')
					i ++;
			}
			else if (cmd[j][i] == '$'
				&& ((cmd[j][i + 1] >= 'a' && cmd[j][i + 1] <= 'z')
					|| (cmd[j][i + 1] >= 'A' && cmd[j][i + 1] <= 'Z')
					|| cmd[j][i + 1] == '_' || cmd[j][i + 1] == '?'))
			{
				cmd[j] = replace_with_env(cmd[j], i, minishell);
				i = -1;
				count = 0;
			}
			else if (cmd[j][i] == '$'
				&& (cmd[j][i + 1] == '\'' || cmd[j][i + 1] == '\"'))
			{
				if (count % 2 == 0)
				{
					cmd[j] = replace_with_env(cmd[j], i, minishell);
					i = -1;
					count = 0;
				}
			}
			i ++;
		}
		i = 0;
		j ++;
	}
}

char	*join_all(char **cmd, t_mini *minishell)
{
	char	*s;
	char	*tmp;
	char	*space;
	int		i;

	i = 1;
	s = ft_strdup(cmd[0]);
	if (s == NULL)
		clear_all_malloc_failed(minishell);
	while (cmd[i] != NULL)
	{
		space = ft_strjoin(s, " ");
		if (space == NULL)
		{
			free(s);
			clear_all_malloc_failed(minishell);
		}
		tmp = ft_strjoin(space, cmd[i]);
		free(s);
		free(space);
		if (tmp == NULL)
			clear_all_malloc_failed(minishell);
		s = ft_strdup(tmp);
		free(tmp);
		if (s == NULL)
			clear_all_malloc_failed(minishell);
		i ++;
	}
	return (s);
}

int	len_of_cmd(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i ++;
			while (s[i] != '\'')
				i ++;
			len += 1;
			i ++;
		}
		else if (s[i] == '\"')
		{
			i ++;
			while (s[i] != '\"')
				i ++;
			len += 1;
			i ++;
		}
		else
		{
			len += 1;
			while (s[i] != '\0' && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
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
			while (s[i] != '\0' && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
				i ++;
		}
	}
	return (len);
}

int	len_of_word(char *s)
{
	int	i;

	i = 0;
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
		else if (s[i] == '\0' || s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
			return (i);
		i ++;
	}
	return (i);
}

char	**split_all(char *s, t_mini *minishell)
{
	char	**new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (len_of_cmd(s) + 1));
	if (new == NULL)
		clear_all_malloc_failed(minishell);
	while (s[i] != '\0')
	{
		len = len_of_word(&s[i]);
		new[j] = copy(&s[i], len);
		if (new[j] == NULL)
		{
			clear_mat(new);
			clear_all_malloc_failed(minishell);
		}
		i += len;
		while (s[i] != '\0' && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
			i ++;
		j ++;
	}
	new[j] = NULL;
	return (new);
}

char	**join_split(char **cmd, t_mini *minishell)
{
	char	*tmp;

	tmp = join_all(cmd, minishell);
	clear_mat(cmd);
	cmd = split_all(tmp, minishell);
	free(tmp);
	return (cmd);
}

void	expend(t_mini *minishell)
{
	int		count;
	t_cmd	*tmp;

	count = 0;
	tmp = minishell->cmd;
	while (tmp != NULL)
	{
		expend_utils(tmp->cmd, minishell, count);
		if (tmp->cmd[0] != NULL)
			tmp->cmd = join_split(tmp->cmd, minishell);
		remove_quotes(tmp, minishell);
		tmp = tmp->next;
	}
}
