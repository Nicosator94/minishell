/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 07:27:15 by niromano          #+#    #+#             */
/*   Updated: 2023/10/02 10:29:05 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**separate_env(char *s)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * 3);
	while (s[i] != '=')
		i ++;
	i ++;
	tmp[0] = malloc(sizeof(char) * i);
	ft_strlcpy(tmp[0], s, i);
	tmp[1] = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	ft_strlcpy(tmp[1], &s[i], ft_strlen(s) - i + 1);
	tmp[2] = NULL;
	return (tmp);
}

t_env	*fill_env(char **tmp)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	new_env->name = ft_strdup(tmp[0]);
	new_env->value = ft_strdup(tmp[1]);
	new_env->next = NULL;
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (new_env);
}

t_env	*create_without_env(void)
{
	t_env	*own_env;
	t_env	*next;
	char	*pwd;

	own_env = malloc(sizeof(t_env));
	own_env->name = ft_strdup("PWD");
	pwd = getcwd(NULL, 100);
	own_env->value = ft_strdup(pwd);
	free(pwd);
	next = malloc(sizeof(t_env));
	own_env->next = next;
	next->name = ft_strdup("SHLVL");
	next->value = ft_strdup("1");
	next->next = NULL;
	return (own_env);
}

t_env	*create_own_env(char **env)
{
	t_env	*start_env;
	t_env	*own_env;
	t_env	*new_env;
	char	**tmp;
	int		i;

	tmp = separate_env(env[0]);
	own_env = fill_env(tmp);
	start_env = own_env;
	i = 1;
	while (env[i] != NULL)
	{
		tmp = separate_env(env[i]);
		new_env = fill_env(tmp);
		own_env->next = new_env;
		own_env = new_env;
		i ++;
	}
	return (start_env);
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
