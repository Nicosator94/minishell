/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_w_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:31:26 by niromano          #+#    #+#             */
/*   Updated: 2023/10/11 15:24:01 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_malloc_failed(t_env *env, int trig)
{
	if (trig == 1)
	{
		free(env->value);
		free(env->name);
		free(env);
	}
	ft_putstr_fd("Malloc Failed !\n", 2);
	return (1);
}

t_env	*create_without_env2(void)
{
	t_env	*own_env;

	own_env = malloc(sizeof(t_env));
	if (own_env == NULL)
		exit(print_malloc_failed(own_env, 0));
	own_env->name = ft_strdup("PWD");
	if (own_env->name == NULL)
	{
		free(own_env);
		exit(print_malloc_failed(own_env, 0));
	}
	own_env->value = getcwd(NULL, 0);
	if (own_env->value == NULL)
	{
		free(own_env->name);
		free(own_env);
		exit(print_malloc_failed(own_env, 0));
	}
	return (own_env);
}

t_env	*create_without_env(void)
{
	t_env	*own_env;
	t_env	*next;

	own_env = create_without_env2();
	next = malloc(sizeof(t_env));
	if (next == NULL)
		exit(print_malloc_failed(own_env, 1));
	own_env->next = next;
	next->name = ft_strdup("SHLVL");
	if (next->name == NULL)
	{
		free(next);
		exit(print_malloc_failed(own_env, 1));
	}
	next->value = ft_strdup("1");
	if (next->value == NULL)
	{
		free(next->name);
		free(next);
		exit(print_malloc_failed(own_env, 1));
	}
	next->next = NULL;
	return (own_env);
}
