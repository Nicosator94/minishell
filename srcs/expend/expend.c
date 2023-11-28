/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 10:17:45 by niromano          #+#    #+#             */
/*   Updated: 2023/11/28 10:51:21 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_all(char **cmd, t_mini *minishell, int i)
{
	char	*s;
	char	*tmp;
	char	*space;

	s = ft_strdup(cmd[0]);
	if (s == NULL)
		clear_all_malloc_failed(minishell);
	while (cmd[i] != NULL)
	{
		space = ft_strjoin(s, " ");
		free(s);
		if (space == NULL)
			clear_all_malloc_failed(minishell);
		tmp = ft_strjoin(space, cmd[i]);
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

char	**join_split(char **cmd, t_mini *minishell)
{
	char	*tmp;

	tmp = join_all(cmd, minishell, 1);
	clear_mat(cmd);
	cmd = split_all(tmp, minishell);
	free(tmp);
	return (cmd);
}

char	*expend_files_utils(char *file, t_mini *minishell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (file[i] != '\0')
	{
		if (file[i] == '\"')
			count += 1;
		if (file[i] == '\'' && count % 2 == 0)
		{
			i ++;
			while (file[i] != '\'')
				i ++;
		}
		if (check_after_dollar_files(file, i, count) > 0)
		{
			file = replace_with_env(file, i, minishell);
			i = -1;
			count = 0;
		}
		i ++;
	}
	return (file);
}

void	expend_files(t_redi *file, t_mini *minishell)
{
	t_redi	*tmp;

	tmp = file;
	while (tmp != NULL)
	{
		if (tmp->status != 3)
			tmp->file = expend_files_utils(tmp->file, minishell);
		tmp = tmp->next;
	}
}

void	expend(t_mini *minishell)
{
	t_cmd	*tmp;

	tmp = minishell->cmd;
	while (tmp != NULL)
	{
		expend_utils(tmp->cmd, minishell);
		if (tmp->cmd[0] != NULL)
			tmp->cmd = join_split(tmp->cmd, minishell);
		expend_files(tmp->file, minishell);
		remove_quotes(tmp, minishell);
		tmp = tmp->next;
	}
	create_here_doc(minishell);
}
