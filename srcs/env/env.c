/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 07:27:15 by niromano          #+#    #+#             */
/*   Updated: 2023/10/12 07:36:21 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**return_malloc_failed(char **tmp)
{
	free(tmp);
	return (NULL);
}

static int	print_malloc_failed(char **tmp, t_env *env, int trig)
{
	if (trig == 1)
	{
		free(tmp[1]);
		free(tmp[0]);
		free(tmp);
	}
	else if (trig == 2)
		clear_env(env);
	else if (trig == 3)
	{
		free(tmp[1]);
		free(tmp[0]);
		free(tmp);
		clear_env(env);
	}
	ft_putstr_fd("Malloc Failed !\n", 2);
	return (1);
}

char	**separate_env(char *s)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * 3);
	if (tmp == NULL)
		return (NULL);
	while (s[i] != '=')
		i ++;
	i ++;
	tmp[0] = malloc(sizeof(char) * i);
	if (tmp[0] == NULL)
		return (return_malloc_failed(tmp));
	ft_strlcpy(tmp[0], s, i);
	tmp[1] = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (tmp[1] == NULL)
	{
		free(tmp[0]);
		return (return_malloc_failed(tmp));
	}
	ft_strlcpy(tmp[1], &s[i], ft_strlen(s) - i + 1);
	tmp[2] = NULL;
	return (tmp);
}

t_env	*first_env_of_list(char **env)
{
	char	**tmp;
	t_env	*own_env;

	tmp = separate_env(env[0]);
	if (tmp == NULL)
		exit(print_malloc_failed(tmp, NULL, 0));
	own_env = fill_env(tmp);
	if (own_env == NULL)
		exit(print_malloc_failed(tmp, NULL, 1));
	return (own_env);
}

t_env	*create_own_env(char **env)
{
	t_env	*start_env;
	t_env	*own_env;
	t_env	*new_env;
	char	**tmp;
	int		i;

	own_env = first_env_of_list(env);
	start_env = own_env;
	i = 1;
	while (env[i] != NULL)
	{
		tmp = separate_env(env[i]);
		if (tmp == NULL)
			exit(print_malloc_failed(tmp, start_env, 2));
		new_env = fill_env(tmp);
		if (new_env == NULL)
			exit(print_malloc_failed(tmp, start_env, 3));
		own_env->next = new_env;
		own_env = new_env;
		i ++;
	}
	return (start_env);
}
