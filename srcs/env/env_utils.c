/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:09:17 by niromano          #+#    #+#             */
/*   Updated: 2023/10/24 10:52:34 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_shlvl(t_env *env)
{
	int		shlvl;

	while (env != NULL)
	{
		if (ft_strncmp(env->name, "SHLVL", 6) == 0)
		{
			shlvl = ft_atoi(env->value);
			free(env->value);
			env->value = ft_itoa(shlvl + 1);
			if (env->value == NULL)
			{
				clear_env(env);
				ft_putstr_fd("Malloc Failed !\n", 2);
				exit (1);
			}
		}
		env = env->next;
	}
}

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
	new_env->val = 1;
	return (new_env);
}

void	clear_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		if (env->name != NULL)
			free(env->name);
		if (env->value != NULL && env->value[0] != '\0')
			free(env->value);
		tmp = env;
		env = env->next;
		free(tmp);
	}
	free(env);
}
