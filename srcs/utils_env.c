/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:09:17 by niromano          #+#    #+#             */
/*   Updated: 2023/10/02 11:11:21 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
