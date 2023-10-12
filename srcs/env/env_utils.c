/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:09:17 by niromano          #+#    #+#             */
/*   Updated: 2023/10/12 07:36:24 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*fill_env(char **tmp)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (new_env == NULL)
		return (NULL);
	new_env->name = ft_strdup(tmp[0]);
	if (new_env->name == NULL)
	{
		free(new_env);
		return (NULL);
	}
	new_env->value = ft_strdup(tmp[1]);
	if (new_env->value == NULL)
	{
		free(new_env->name);
		free(new_env);
		return (NULL);
	}
	new_env->next = NULL;
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (new_env);
}

void	clear_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		free(env->name);
		free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
	free(env);
}

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

char	**list_to_matrix(t_env *env)
{
	char	**mat;
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	mat = malloc(sizeof(char *) * (size_env(env) + 1));
	while (env != NULL)
	{
		tmp1 = ft_strdup(env->name);
		tmp2 = ft_strjoin(tmp1, "=");
		free(tmp1);
		mat[i] = ft_strjoin(tmp2, env->value);
		free(tmp2);
		mat[i][ft_strlen(env->name) + ft_strlen(env->value) + 1] = '\0';
		env = env->next;
		i ++;
	}
	mat[i] = NULL;
	return (mat);
}
