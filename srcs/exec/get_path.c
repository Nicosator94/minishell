/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:11:38 by niromano          #+#    #+#             */
/*   Updated: 2023/10/23 10:44:02 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_list_of_path(t_env *env)
{
	char	**list_of_path;
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL && ft_strncmp(tmp->name, "PATH", 5) != 0)
		tmp = tmp->next;
	if (tmp != NULL && ft_strncmp(tmp->name, "PATH", 5) == 0)
	{
		list_of_path = ft_split(tmp->value, ':');
		return (list_of_path);
	}
	return (NULL);
}

void	free_get_path(char **path_of_env, char *tmp)
{
	int	i;

	i = 0;
	while (path_of_env != NULL && path_of_env[i] != NULL)
	{
		free(path_of_env[i]);
		i ++;
	}
	if (path_of_env != NULL)
		free(path_of_env);
	if (tmp != NULL)
		free(tmp);
}

char	*get_path(char *cmd, t_env *env)
{
	char	*path;
	char	**path_of_env;
	char	*tmp;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	if (cmd[0] == '.' || cmd[0] == '/')
		return (ft_strdup(cmd));
	path_of_env = get_list_of_path(env);
	tmp = ft_strjoin("/", cmd);
	while (path_of_env != NULL && path_of_env[i] != NULL)
	{
		path = ft_strjoin(path_of_env[i], tmp);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_get_path(path_of_env, tmp);
			return (path);
		}
		free(path);
		i ++;
	}
	free_get_path(path_of_env, tmp);
	return (NULL);
}
