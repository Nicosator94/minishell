/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:11:38 by niromano          #+#    #+#             */
/*   Updated: 2023/11/21 08:43:50 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_list_of_path(t_mini *minishell)
{
	char	**list_of_path;
	t_env	*tmp;

	tmp = minishell->env;
	while (tmp != NULL && ft_strncmp(tmp->name, "PATH", 5) != 0)
		tmp = tmp->next;
	if (tmp != NULL && ft_strncmp(tmp->name, "PATH", 5) == 0)
	{
		list_of_path = ft_split(tmp->value, ':');
		if (list_of_path == NULL)
			clear_all_malloc_failed(minishell);
		return (list_of_path);
	}
	list_of_path = malloc(sizeof(char *) * 2);
	if (list_of_path == NULL)
		clear_all_malloc_failed(minishell);
	list_of_path[0] = getcwd(NULL, 0);
	list_of_path[1] = NULL;
	return (list_of_path);
}

char	*test_all_path(char	**path_of_env, char *tmp, char *path, t_mini *mini)
{
	int	i;

	i = 0;
	while (path_of_env != NULL && path_of_env[i] != NULL)
	{
		path = ft_strjoin(path_of_env[i], tmp);
		if (path == NULL)
		{
			clear_mat(path_of_env);
			clear_all_malloc_failed(mini);
		}
		if (access(path, F_OK | X_OK) == 0)
		{
			clear_mat(path_of_env);
			free(tmp);
			return (path);
		}
		free(path);
		i ++;
	}
	clear_mat(path_of_env);
	free(tmp);
	return (NULL);
}

char	*get_path(char *cmd, t_mini *minishell)
{
	char	*path;
	char	**path_of_env;
	char	*tmp;

	path = NULL;
	if (cmd == NULL)
		return (NULL);
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		path = ft_strdup(cmd);
		if (path == NULL)
			clear_all_malloc_failed(minishell);
		return (path);
	}
	path_of_env = get_list_of_path(minishell);
	tmp = ft_strjoin("/", cmd);
	if (tmp == NULL)
	{
		clear_mat(path_of_env);
		clear_all_malloc_failed(minishell);
	}
	path = test_all_path(path_of_env, tmp, path, minishell);
	return (path);
}
