/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:57:49 by niromano          #+#    #+#             */
/*   Updated: 2023/10/25 08:06:02 by niromano         ###   ########.fr       */
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

char	**list_to_matrix(t_mini *minishell)
{
	t_env	*tmp;
	char	**mat;
	int		i;

	i = 0;
	mat = malloc(sizeof(char *) * (size_env(minishell->env) + 1));
	if (mat == NULL)
		clear_all_malloc_failed(minishell);
	tmp = minishell->env;
	while (tmp != NULL)
	{
		mat[i] = list_to_string_to_matrix(tmp->name, tmp->value);
		if (mat[i] == NULL)
		{
			clear_mat(mat);
			clear_all_malloc_failed(minishell);
		}
		tmp = tmp->next;
		i ++;
	}
	mat[i] = NULL;
	return (mat);
}
