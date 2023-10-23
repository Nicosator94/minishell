/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:57:49 by niromano          #+#    #+#             */
/*   Updated: 2023/10/19 02:16:36 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_env(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		env = env->next;
		i ++;
	}
	return (i);
}

void	clear_mat_of_env(char **mat, t_env *env, t_cmd *start_cmd)
{
	int	i;

	i = 0;
	while (mat[i] != NULL)
	{
		free(mat[i]);
		i ++;
	}
	free(mat);
	all_clear_command(env, start_cmd);
}

char	*list_to_string_to_matrix(char *name, char *value)
{
	char	*tmp1;
	char	*tmp2;
	char	*new_s;

	tmp1 = ft_strdup(name);
	if (tmp1 == NULL)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, "=");
	free(tmp1);
	if (tmp2 == NULL)
		return (NULL);
	new_s = ft_strjoin(tmp2, value);
	free(tmp2);
	if (new_s == NULL)
		return (NULL);
	new_s[ft_strlen(name) + ft_strlen(value) + 1] = '\0';
	return (new_s);
}

char	**list_to_matrix(t_env *env, t_cmd *start_cmd)
{
	char	**mat;
	int		i;

	i = 0;
	mat = malloc(sizeof(char *) * (size_env(env) + 1));
	if (mat == NULL)
		all_clear_command(env, start_cmd);
	while (env != NULL)
	{
		mat[i] = list_to_string_to_matrix(env->name, env->value);
		if (mat[i] == NULL)
			clear_mat_of_env(mat, env, start_cmd);
		env = env->next;
		i ++;
	}
	mat[i] = NULL;
	return (mat);
}
